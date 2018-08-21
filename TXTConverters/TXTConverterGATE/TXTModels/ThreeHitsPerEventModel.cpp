#include "ThreeHitsPerEventModel.h"
#include "TVector3.h"
#include "TFile.h"
#include "../../../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../../../Tools/ToolsForROOT/ReadAndSave.h"
#include <math.h>  

ThreeHitsPerEventModel::ThreeHitsPerEventModel() { initHistograms(); }
ThreeHitsPerEventModel::~ThreeHitsPerEventModel() { deleteHistograms(); }

void ThreeHitsPerEventModel::analyzeEntry()
{
 if ( fCurrentEventsNumberSaved == fEventsNumberToSave )
 {
  fCreator->stopJob();
  return;
 }

 TXTData data = *( dynamic_cast< TXTData* >( fCreator->getData() ) );
 if ( data.getEventID() != fEventID )
 {
  if ( fEventID > -1 )
   analyzeEvent();
  fEventID = data.getEventID();
  fDatas.clear();
 }
 fDatas.push_back( data );
}

void ThreeHitsPerEventModel::setCreator( TXTDataCreator* creator ) { fCreator = creator; }

void ThreeHitsPerEventModel::setOutputFileName( std::string output_file_name ) 
{
 fTXTFileName = output_file_name + ".txt";
 fControlROOTFileName = output_file_name + "_control_histograms.root";
}

void ThreeHitsPerEventModel::setEventsNumberToSave( unsigned int events_to_generate ) { fEventsNumberToSave = events_to_generate; }

void ThreeHitsPerEventModel::initHistograms()
{
 h1EnergyDeposition = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDeposition", 371 * 4, -0.5, 370.5, "#Delta E [keV]", "Counts" );
 h2HitPositionXY = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXY", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "y [cm]" );
 h2HitPositionXZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "z [cm]" );
 h2HitPositionYZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionYZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "y [cm]", "z [cm]" );
 h2ScattersPerTrack_1_vs_2 = ToolsForROOT::HistogramsCreator::getTH2F( "h2ScattersPerTrack_1_vs_2", 5, -0.5, 4.5, 5, -0.5, 4.5, "Number of scatters per track 1", "Number of scatters per track 2" );
 h2ScattersPerTrack_1_vs_3 = ToolsForROOT::HistogramsCreator::getTH2F( "h2ScattersPerTrack_1_vs_3", 5, -0.5, 4.5, 5, -0.5, 4.5, "Number of scatters per track 1", "Number of scatters per track 3" );
 h2ScattersPerTrack_2_vs_3 = ToolsForROOT::HistogramsCreator::getTH2F( "h2ScattersPerTrack_2_vs_3", 5, -0.5, 4.5, 5, -0.5, 4.5, "Number of scatters per track 2", "Number of scatters per track 3" );
 h1ScatteringKind = ToolsForROOT::HistogramsCreator::getTH1F( "h1ScatteringKind", 5, -0.5, 4.5, "Scattering type", "Counts" );
}

void ThreeHitsPerEventModel::deleteHistograms()
{
 if ( fHistogramSavedToFile )
  return;
 delete h1EnergyDeposition;
 delete h2HitPositionXY;
 delete h2HitPositionXZ;
 delete h2HitPositionYZ;
 delete h2ScattersPerTrack_1_vs_2;
 delete h2ScattersPerTrack_1_vs_3;
 delete h2ScattersPerTrack_2_vs_3;
 delete h1ScatteringKind;
}

void ThreeHitsPerEventModel::saveHistograms()
{
 TFile* file = ToolsForROOT::ReadAndSave::createFile( fControlROOTFileName, true ); 
 if ( !file )
  return;

 std::cout << "Saving histograms .. " << std::endl;
 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDeposition );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionXY );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionXZ );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionYZ );

 ToolsForROOT::ReadAndSave::saveToFile( file, h2ScattersPerTrack_1_vs_2 );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2ScattersPerTrack_1_vs_3 );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2ScattersPerTrack_2_vs_3 );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1ScatteringKind );

 ToolsForROOT::ReadAndSave::closeFile( file );
 fTXTFile.close();

 fHistogramSavedToFile = true;

 std::cout << "Saved " << fCurrentEventsNumberSaved << " events from " << fEventsNumberToSave << " required " << std::endl;
 double status = 100.0 * static_cast<double>( fCurrentEventsNumberSaved ) / static_cast<double>( fEventsNumberToSave );
 std::cout << " Task accomplished in " << status << " prercents" << std::endl;

 std::cout << "fTotalEventsNumber = " << fTotalEventsNumber << std::endl;
 std::cout << "fFirstCondition = " << fFirstCondition << std::endl;
 std::cout << "fSecondCondition = " << fSecondCondition << std::endl;
 std::cout << "fThirdCondition = " << fThirdCondition << std::endl;
}

void ThreeHitsPerEventModel::analyzeEvent()
{

 ++fTotalEventsNumber;

 if ( !conditionHitsNumber() )
  return;
 ++fFirstCondition;

 if ( !conditionHitsScintilators() )
  return;
 ++fSecondCondition;

 if ( !conditionEnergyConditionForFirstScatter() )
  return;
 ++fThirdCondition;

 if ( !fIsOpenedTXTFile)
 {
  fTXTFile.open( fTXTFileName.c_str(), std::ios::out );
  fIsOpenedTXTFile = true;
 }

 ++fCurrentEventsNumberSaved;

 //OK - lets start extraction of data

 int eventID = fDatas[ 0 ].getEventID();
 double trackID, x, y, z, t, dE;
 TVector3 hit_pos;
 unsigned int scatters_per_track1 =0, scatters_per_track2 = 0, scatters_per_track3 = 0;

 for ( std::vector<TXTData>::iterator it = fDatas.begin(); it != fDatas.end(); ++it )
 {
  trackID = it->getTrackID();

  switch ( it->getTrackID() )
  {
   case 1:
    ++scatters_per_track1;
    break;
   case 2:
    ++scatters_per_track2;
    break;
   case 3:
    ++scatters_per_track3;
    break;
  };

  hit_pos = it->getHitPosition();
  x = hit_pos.x();
  y = hit_pos.y(); 
  z = hit_pos.z();
  t = it->getTime();
  dE = it->getEnergyDeposition();

  double t_int_part = 0, t_fraction_part = 0;
  t_fraction_part = modf( t, &t_int_part );
  while ( true )
  {
   if ( t_int_part > kWindowSize )
    t_int_part -= kWindowSize;
   else
    break;
  }
  t = t_int_part + t_fraction_part;

  fTXTFile << eventID << " " << trackID << " " << std::setprecision (8) << x << " " << y << " " << z << " " << std::setprecision (8) << t << " " << std::setprecision (7) << dE << std::endl;

  h1EnergyDeposition->Fill( dE );
  h2HitPositionXY->Fill( x, y );
  h2HitPositionXZ->Fill( x, z );
  h2HitPositionYZ->Fill( y, z );
 }
 
 h2ScattersPerTrack_1_vs_2->Fill( scatters_per_track1, scatters_per_track2 );
 h2ScattersPerTrack_1_vs_3->Fill( scatters_per_track1, scatters_per_track3 );
 h2ScattersPerTrack_2_vs_3->Fill( scatters_per_track2, scatters_per_track3 );

 int scttering_kind = 0;

 if ( scatters_per_track1 == 3 || scatters_per_track2 == 3 || scatters_per_track3 == 3 )
  scttering_kind = 3;
 else if ( scatters_per_track1 == 2 || scatters_per_track2 == 2 || scatters_per_track3 == 2 )
  scttering_kind = 2;
 else
  scttering_kind = 1;

 h1ScatteringKind->Fill( scttering_kind );
}

bool ThreeHitsPerEventModel::conditionHitsNumber() { return fDatas.size() == kRequiredHitsNumber; }

bool ThreeHitsPerEventModel::conditionHitsScintilators()
{
 TVector3 sci1 = fDatas[ 0 ].getScintilatorPosition();
 TVector3 sci2 = fDatas[ 1 ].getScintilatorPosition();
 TVector3 sci3 = fDatas[ 2 ].getScintilatorPosition();

 return sci1 != sci2 && sci1 != sci3 && sci2 != sci3;
}

bool ThreeHitsPerEventModel::conditionEnergyConditionForFirstScatter()
{
 for ( unsigned int i = 0; i < 3; ++i )
 {
  if ( fDatas[ i ].getScatteringIndex() == 1 && fDatas[ i ].getEnergy() != fDatas[ i ].getEmissionEnergy() )
   return false;
 }
 return true;
}
