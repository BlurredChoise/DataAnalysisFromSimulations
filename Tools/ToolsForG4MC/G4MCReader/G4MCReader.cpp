#include <iostream>
#include <JPetWriter/JPetWriter.h>
#include <JPetAnalysisTools/JPetAnalysisTools.h>
#include <JPetOptionsTools/JPetOptionsTools.h>
#include "G4MCReader.h"

#include <JPetScin/JPetScin.h>
#include <TMath.h>

using namespace jpet_options_tools;

namespace ToolsForG4MC
{
 G4MCReader::G4MCReader( const char* name ) : JPetUserTask( name ) { }

 G4MCReader::~G4MCReader() { }

 bool G4MCReader::init()
 {
   std::unique_ptr<JPetGeomMapping> fDetectorMap( new JPetGeomMapping( getParamBank() ) );
   INFO( "G4MCReader started." );
  return true;
 }

 bool G4MCReader::exec()
 { 
  if ( auto& mcEventPack = dynamic_cast<JPetGeantEventPack* const>( fEvent ) )
   processMonteCarloEvent( mcEventPack );
  else
   return false;
  return true;
 }

 bool G4MCReader::terminate()
 {
  INFO( "MC events processing ended?" );
  return true;
 }

 void G4MCReader::processMonteCarloEvent( JPetGeantEventPack* event_pack )
 {
  fHitsFromMonteCarlo.clear();
  unsigned int number_of_hits_per_event = event_pack->GetNumberOfHits();
  fHitsFromMonteCarlo.resize( number_of_hits_per_event );
  for ( unsigned int i = 0; i < number_of_hits_per_event; ++i )
  {
   JPetGeantScinHits* raw_hit = event_pack->GetHit( i );
   fHitsFromMonteCarlo[ i ] = convertData( raw_hit );
  }
 }

 G4MCHitData G4MCReader::convertData( JPetGeantScinHits* raw_hit_data )
 {
  if ( fLastEventID != raw_hit_data->GetEvtID() )
  {
   fLastEventID = raw_hit_data->GetEvtID();
   fLastTrackID = raw_hit_data->GetTrackID();
   fScatteringIndex = 1;
  }
  else if ( fLastTrackID != raw_hit_data->GetTrackID() )
  {
   fLastTrackID = raw_hit_data->GetTrackID();
   fScatteringIndex = 1;
  }
  else
  {
   ++fScatteringIndex;
  }

  G4MCHitData hit_data;
  hit_data.setEnergyDeposition( raw_hit_data->GetEneDepos() );
  hit_data.setEventID( raw_hit_data->GetEvtID() );
  hit_data.setTrackID( raw_hit_data->GetTrackID() );
  hit_data.setHitPosition( raw_hit_data->GetHitPosition() );

  double radius = getParamBank().getScintillator( raw_hit_data->GetScinID() ).getBarrelSlot().getLayer().getRadius();
  double theta = TMath::DegToRad() * getParamBank().getScintillator( raw_hit_data->GetScinID() ).getBarrelSlot().getTheta();

  TVector3 scitillator_position( radius * std::cos(theta), radius * std::sin(theta), 0 );

  hit_data.setScintilatorPosition( scitillator_position );
  hit_data.setTime( raw_hit_data->GetTime() );

  hit_data.setScatteringIndex( fScatteringIndex );

  G4MCHitData::GammaKind kind;
  switch ( raw_hit_data->GetGenGammaMultiplicity() )
  {
   case 1:
    kind = G4MCHitData::GammaKind::Prompt;
    break;
   case 2:
    kind = G4MCHitData::GammaKind::ParaPositronium;
    break;
   case 3:
    kind = G4MCHitData::GammaKind::OrtoPositronium;
    break;  
  };

  hit_data.setGammaKind( kind );
  return hit_data;
 }

 std::vector< G4MCHitData >* G4MCReader::getHitsData() { return &fHitsFromMonteCarlo; }

};
