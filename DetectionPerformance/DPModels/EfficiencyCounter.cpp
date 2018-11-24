#include "EfficiencyCounter.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "../../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../../Tools/ToolsForROOT/ReadAndSave.h"
#include <vector>
#include "../DPData.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class perform analysis of data from simulation and calc efficency
File: EfficiencyCounter.cpp
**/

EfficiencyCounter::EfficiencyCounter() { initHistograms(); }

EfficiencyCounter::~EfficiencyCounter() {}

void EfficiencyCounter::analyzeEntry()
{
 DPData data = *( dynamic_cast< DPData* >( fCreator->getData() ) );
 //++fCounterAE;
 if ( data.getEventID() != fEventID )
 {
  if ( fEventID > -1 )
   analyzeEvent();
  fEventID = data.getEventID();
  fDatas.clear();
 }
 fDatas.push_back( data );
}

void EfficiencyCounter::setCreator( DPDataCreator* creator ) { fCreator = creator; }

void EfficiencyCounter::setOutputFileName( std::string output_file_name ) { fOutputFileName = output_file_name; }

void EfficiencyCounter::setSourceModelName( std::string source_model_name ) { fSourceModelName = source_model_name; }

void EfficiencyCounter::setGeometryNumber( unsigned int geometry_number ) { fGeometryNumber = geometry_number; }

void EfficiencyCounter::setNumberOfGeneratedEvents( unsigned int number_of_generated_events ) { fNumberOfGeneratedEvents = number_of_generated_events; }

void EfficiencyCounter::setNumberOdGammasGeneratedPerEvent( unsigned int number_of_generated_gammas_per_events ) 
{ 
 fNumberOfGammasGeneratedPerEvent = number_of_generated_gammas_per_events; 
 fCounterTracks = std::vector<unsigned int>(number_of_generated_gammas_per_events,0);
}

void EfficiencyCounter::setEnergyThreshold( double energy_threshold ) { fEnergyThreshold = energy_threshold; }

void EfficiencyCounter::setPromptEnergyThreshold( double energy_threshold ) { fPromptEnergyThreshold = energy_threshold; }

void EfficiencyCounter::setPromptEnergy( double energy ) { fPromptEnergy = energy; }

void EfficiencyCounter::setPromptVisible( bool prompts_here ) { fPromptInData = prompts_here; }

void EfficiencyCounter::initHistograms()
{
 h2XYHitPosition = ToolsForROOT::HistogramsCreator::getTH2F( "h2XYHitPosition", 120 * 10, -60.0, 60.0, 120 * 10, -60.0, 60.0, "x [cm]", "y [cm]" );
 h2XZHitPosition = ToolsForROOT::HistogramsCreator::getTH2F( "h2XZHitPosition", 120 * 10, -60.0, 60.0, 50 * 10, -25.0, 25.0, "x [cm]", "z [cm]" );
 h2YZHitPosition = ToolsForROOT::HistogramsCreator::getTH2F( "h2YZHitPosition", 120 * 10, -60.0, 60.0, 50 * 10, -25.0, 25.0, "y [cm]", "z [cm]" );

 h2XYHitPositionAccepted = ToolsForROOT::HistogramsCreator::getTH2F( "h2XYHitPositionAccepted", 120 * 10, -60.0, 60.0, 120 * 10, -60.0, 60.0, "x [cm]", "y [cm]" );
 h2XZHitPositionAccepted = ToolsForROOT::HistogramsCreator::getTH2F( "h2XZHitPositionAccepted", 120 * 10, -60.0, 60.0, 50 * 10, -25.0, 25.0, "x [cm]", "z [cm]" );
 h2YZHitPositionAccepted = ToolsForROOT::HistogramsCreator::getTH2F( "h2YZHitPositionAccepted", 120 * 10, -60.0, 60.0, 50 * 10, -25.0, 25.0, "y [cm]", "z [cm]" );

 h1NumberOfScattersPerTrack = ToolsForROOT::HistogramsCreator::getTH1F( "h1NumberOfScattersPerTrack", 31, -0.5, 30.5, "Number of scatters per track", "Counts" );
 h1NumberOfScatteringPerTracksSet = ToolsForROOT::HistogramsCreator::getTH1F( "h1NumberOfScatteringPerTracksSet", 11, -0.5, 10.5, "Minimum number of scatters per tracks set", "Counts" );
 h1NumberOfScattersPerTrackAccepted = ToolsForROOT::HistogramsCreator::getTH1F( "h1NumberOfScattersPerTrackAccepted", 31, -0.5, 30.5, "Number of scatters per track", "Counts" );
 h1EnergyDepositionAcceptedBeforeCuts = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDepositionAcceptedBeforeCuts", 2001 * 10, -0.5, 2000.5, "#Delta E [keV]", "Counts" );
 h1EnergyDepositionAcceptedAfterCuts = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDepositionAcceptedAfterCuts", 2001 * 10, -0.5, 2000.5, "#Delta E [keV]", "Counts" );

 h1GammaEnergyAll = ToolsForROOT::HistogramsCreator::getTH1F( "h1GammaEnergyAll", 2001 * 10, -0.5, 2000.5, "E [keV]", "Counts" );
 h1GammaEnergyAccepted = ToolsForROOT::HistogramsCreator::getTH1F( "h1GammaEnergyAccepted", 2001 * 10, -0.5, 2000.5, "E [keV]", "Counts" );
}

void EfficiencyCounter::saveHistograms( TFile* file )
{
 std::cout << "[EfficiencyCounter] Saving histograms .. " << std::endl;//Accepted
 ToolsForROOT::ReadAndSave::saveToFile( file, h2XYHitPosition );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2XZHitPosition );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2YZHitPosition );

 ToolsForROOT::ReadAndSave::saveToFile( file, h2XYHitPositionAccepted );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2XZHitPositionAccepted );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2YZHitPositionAccepted );

 ToolsForROOT::ReadAndSave::saveToFile( file, h1NumberOfScattersPerTrack );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1NumberOfScatteringPerTracksSet );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1NumberOfScattersPerTrackAccepted );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDepositionAcceptedBeforeCuts );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDepositionAcceptedAfterCuts );

 ToolsForROOT::ReadAndSave::saveToFile( file, h1GammaEnergyAll );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1GammaEnergyAccepted );
}

void EfficiencyCounter::saveResultsToFile() 
{
 double fraction = static_cast<double>( fNumberOfDetectedEvents ) / static_cast<double>( fNumberOfGeneratedEvents ) * 100.0;
 std::fstream f;
 f.open( fOutputFileName.c_str(), std::ios::app );
 f << fSourceModelName << " " << fGeometryNumber << " " << fEnergyThreshold << " " << fPromptEnergyThreshold << " " << fNumberOfDetectedEvents << " " << fNumberOfGeneratedEvents << " " << fraction << std::endl;
 f.close();

 std::cout << "fCounterTotal           = " << fCounterTotal << std::endl;
 std::cout << "fCounterSize            = " << fCounterSize << std::endl;
 std::cout << "fCounterFoundTracks     = " << fCounterFoundTracks << std::endl;
 std::cout << "fCounterScintilators    = " << fCounterScintilators << std::endl;
 std::cout << "fNumberOfDetectedEvents = " << fNumberOfDetectedEvents << std::endl;
 std::cout << " fCounterAE " << fCounterAE << std::endl;

}

void EfficiencyCounter::analyzeEvent()
{
 ++fCounterTotal;

 std::vector< unsigned int > raw_scatters( fNumberOfGammasGeneratedPerEvent, 0 );
 unsigned int index = 0;
 assert(fDatas.size()>0);
//assert(fNumberOfGammasGeneratedPerEvent ==2);
 for ( std::vector<DPData>::iterator it = fDatas.begin(); it != fDatas.end(); ++it )
 {
  index = static_cast<unsigned int>( it->getTrackID() - 1 );
  //assert(it->getTrackID() ==1 ||it->getTrackID() ==2);
  raw_scatters[ index ] = TMath::Max( raw_scatters[ index ], it->getScatteringIndex() );
  TVector3 v = it->getHitPosition();

  h2XYHitPosition->Fill( v.x(), v.y() );
  h2XZHitPosition->Fill( v.x(), v.z() );
  h2YZHitPosition->Fill( v.y(), v.z() );
  h1GammaEnergyAll->Fill( it->getEnergy() );
 }
 
 for ( std::vector< unsigned int >::iterator it = raw_scatters.begin(); it !=  raw_scatters.end(); ++it )
  h1NumberOfScattersPerTrack->Fill( static_cast<double>( *it ) );

 if ( fDatas.size() < fNumberOfGammasGeneratedPerEvent )
  return;
 ++fCounterSize;



 std::vector<DPData* > hits( fNumberOfGammasGeneratedPerEvent, nullptr );
 
 int datas_size = fDatas.size();
 for ( unsigned int i = 0; i < datas_size; ++i )
 {
  index = static_cast<unsigned int>( fDatas[ i ].getTrackID() - 1 );
  if ( hits[ index ] == nullptr )
   hits[ index ] = &fDatas[ i ];
 }

 for ( unsigned int i = 0; i < fNumberOfGammasGeneratedPerEvent; ++i )
  if ( hits[ i ] == nullptr )
   return;

 ++fCounterFoundTracks;

  for ( unsigned int i = 0; i < fNumberOfGammasGeneratedPerEvent; ++i )
  for ( unsigned int j = 0; j < fNumberOfGammasGeneratedPerEvent; ++j )
   if ( i != j )
    if ( hits[ i ]->getScintilatorPosition() == hits[ j ]->getScintilatorPosition() )
     return;

 ++fCounterScintilators;

 double E0 = 0, dE = 0;

 for ( unsigned int i = 0; i < fNumberOfGammasGeneratedPerEvent; ++i )
 {
  E0 = hits[ i ]->getEmissionEnergy();
  dE = hits[ i ]->getEnergyDeposition();
  h1EnergyDepositionAcceptedBeforeCuts->Fill( dE );

  if ( fPromptInData && TMath::Abs( E0 - fPromptEnergy) < 0.0001 )
  {
    if ( !( dE > fPromptEnergyThreshold ) )
     return;
  }
  else if ( !( dE > fEnergyThreshold ) )
  {
   return;
  }
 }

 ++fNumberOfDetectedEvents;
// if (hits.at(0)->getTrackID() ==hits.at(1)->getTrackID()) {
 // return; 
//} 
++fCounterAE;

 std::vector< unsigned int > scatters( fNumberOfGammasGeneratedPerEvent, 0 );

 for ( std::vector<DPData>::iterator it = fDatas.begin(); it != fDatas.end(); ++it )
 {
  index = static_cast<unsigned int>( it->getTrackID() - 1 );
  scatters[ index ] = TMath::Max( scatters[ index ], it->getScatteringIndex() );
 }

 unsigned int min_common_scatters_number = scatters[ 0 ];
 for ( std::vector< unsigned int >::iterator it = scatters.begin(); it != scatters.end(); ++it )
 {
  h1NumberOfScattersPerTrackAccepted->Fill( static_cast<double>( *it ) );
  min_common_scatters_number = TMath::Min( min_common_scatters_number, *it );
 }
 h1NumberOfScatteringPerTracksSet->Fill( static_cast<double>( min_common_scatters_number ) );

 for ( std::vector<DPData* >::iterator it = hits.begin(); it != hits.end(); ++it )
 {
  TVector3 v = ( *it )->getHitPosition();
  h2XYHitPositionAccepted->Fill( v.x(), v.y() );
  h2XZHitPositionAccepted->Fill( v.x(), v.z() );
  h2YZHitPositionAccepted->Fill( v.y(), v.z() );
  h1EnergyDepositionAcceptedAfterCuts->Fill( ( *it )->getEnergyDeposition() );
  h1GammaEnergyAccepted->Fill( ( *it )->getEnergy() );
 }

}
