#include "EfficiencyPolarizationCounter.h"
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
File: EfficiencyPolarizationCounter.cpp
**/

EfficiencyPolarizationCounter::EfficiencyPolarizationCounter() { initHistograms(); }

EfficiencyPolarizationCounter::~EfficiencyPolarizationCounter() {}

void EfficiencyPolarizationCounter::analyzeEntry()
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

void EfficiencyPolarizationCounter::setCreator( DPDataCreator* creator ) { fCreator = creator; }

void EfficiencyPolarizationCounter::setOutputFileName( std::string output_file_name ) { fOutputFileName = output_file_name; }

void EfficiencyPolarizationCounter::setSourceModelName( std::string source_model_name ) { fSourceModelName = source_model_name; }

void EfficiencyPolarizationCounter::setGeometryNumber( unsigned int geometry_number ) { fGeometryNumber = geometry_number; }

void EfficiencyPolarizationCounter::setNumberOfGeneratedEvents( unsigned int number_of_generated_events ) { fNumberOfGeneratedEvents = number_of_generated_events; }

void EfficiencyPolarizationCounter::setNumberOdGammasGeneratedPerEvent( unsigned int number_of_generated_gammas_per_events ) 
{ 
 fNumberOfGammasGeneratedPerEvent = number_of_generated_gammas_per_events; 
 fCounterTracks = std::vector<unsigned int>(number_of_generated_gammas_per_events,0);
}

void EfficiencyPolarizationCounter::setEnergyThreshold( double energy_threshold ) { fEnergyThreshold = energy_threshold; }

void EfficiencyPolarizationCounter::setPromptEnergyThreshold( double energy_threshold ) { fPromptEnergyThreshold = energy_threshold; }

void EfficiencyPolarizationCounter::setPromptEnergy( double energy ) { fPromptEnergy = energy; }

void EfficiencyPolarizationCounter::setPromptVisible( bool prompts_here ) { fPromptInData = prompts_here; }

void EfficiencyPolarizationCounter::initHistograms()
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

 h1EnergyDepositionAcceptedBeforeCutsFirstScattering = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDepositionAcceptedBeforeCutsFirstScattering", 2001 * 10, -0.5, 2000.5, "#Delta E [keV]", "Counts" );
 h1EnergyDepositionAcceptedAfterCutsFirstScattering = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDepositionAcceptedAfterCutsFirstScattering", 2001 * 10, -0.5, 2000.5, "#Delta E [keV]", "Counts" );

 h1EnergyDepositionAcceptedBeforeCutsSecondScattering = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDepositionAcceptedBeforeCutsSecondScattering", 2001 * 10, -0.5, 2000.5, "#Delta E [keV]", "Counts" );
 h1EnergyDepositionAcceptedAfterCutsSecondScattering = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDepositionAcceptedAfterCutsSecondScattering", 2001 * 10, -0.5, 2000.5, "#Delta E [keV]", "Counts" );

 h1GammaEnergyAll = ToolsForROOT::HistogramsCreator::getTH1F( "h1GammaEnergyAll", 2001 * 10, -0.5, 2000.5, "E [keV]", "Counts" );
 h1GammaEnergyAccepted = ToolsForROOT::HistogramsCreator::getTH1F( "h1GammaEnergyAccepted", 2001 * 10, -0.5, 2000.5, "E [keV]", "Counts" );
}

void EfficiencyPolarizationCounter::saveHistograms( TFile* file )
{
 std::cout << "[EfficiencyPolarizationCounter] Saving histograms .. " << std::endl;//Accepted
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

 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDepositionAcceptedBeforeCutsFirstScattering );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDepositionAcceptedAfterCutsFirstScattering );

 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDepositionAcceptedBeforeCutsSecondScattering );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDepositionAcceptedAfterCutsSecondScattering );

 ToolsForROOT::ReadAndSave::saveToFile( file, h1GammaEnergyAll );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1GammaEnergyAccepted );
}

void EfficiencyPolarizationCounter::saveResultsToFile() 
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

void EfficiencyPolarizationCounter::analyzeEvent()
{
 ++fCounterTotal;

 std::vector< unsigned int > raw_scatters( fNumberOfGammasGeneratedPerEvent, 0 );
 unsigned int index = 0;
 assert(fDatas.size()>0);

 for ( std::vector<DPData>::iterator it = fDatas.begin(); it != fDatas.end(); ++it )
 {
  index = static_cast<unsigned int>( it->getTrackID() - 1 );

  raw_scatters[ index ] = TMath::Max( raw_scatters[ index ], it->getScatteringIndex() );
  TVector3 v = it->getHitPosition();

  h2XYHitPosition->Fill( v.x(), v.y() );
  h2XZHitPosition->Fill( v.x(), v.z() );
  h2YZHitPosition->Fill( v.y(), v.z() );
  h1GammaEnergyAll->Fill( it->getEnergy() );
 }
 
 for ( std::vector< unsigned int >::iterator it = raw_scatters.begin(); it !=  raw_scatters.end(); ++it )
  h1NumberOfScattersPerTrack->Fill( static_cast<double>( *it ) );

 for ( std::vector< unsigned int >::iterator it =  raw_scatters.begin(); it != raw_scatters.end(); ++it )
  if ( *it < 2 )
   return;

 /*std::cout<<std::endl;
 for ( unsigned int i = 0; i < fNumberOfGammasGeneratedPerEvent; ++i )
  std::cout<< i << " " << raw_scatters[i] << std::endl;*/
 
 
 ++fCounterSize;

 struct TwoHits
 {
  DPData* fFirstHit = nullptr;
  DPData* fSecondHit = nullptr;
 };

 TwoHits th;
 std::vector<TwoHits> hits( fNumberOfGammasGeneratedPerEvent, th );
 
 unsigned int datas_size = fDatas.size();
 unsigned int scatter_index = 0;


 for ( unsigned int i = 0; i < datas_size; ++i )
 {
  index = static_cast<unsigned int>( fDatas[ i ].getTrackID() - 1 );
  scatter_index = fDatas[ i ].getScatteringIndex();
  
  if ( scatter_index == 1 )
   hits[ index ].fFirstHit = &fDatas[ i ];
  else if ( scatter_index == 2 )
   hits[ index ].fSecondHit = &fDatas[ i ];
 }

 for ( unsigned int i = 0; i < fNumberOfGammasGeneratedPerEvent; ++i )
  if ( hits[ i ].fFirstHit == nullptr || hits[ i ].fSecondHit == nullptr )
   return;

 ++fCounterFoundTracks;

  for ( unsigned int i = 0; i < fNumberOfGammasGeneratedPerEvent; ++i )
  for ( unsigned int j = 0; j < fNumberOfGammasGeneratedPerEvent; ++j )
   if ( i != j )
    if ( hits[ i ].fFirstHit->getScintilatorPosition() == hits[ j ].fFirstHit->getScintilatorPosition() && hits[ i ].fSecondHit->getScintilatorPosition() == hits[ j ].fSecondHit->getScintilatorPosition() )
     return;

 ++fCounterScintilators;

 double E01 = 0, dE1 = 0;
 double E02 = 0, dE2 = 0;

 for ( unsigned int i = 0; i < fNumberOfGammasGeneratedPerEvent; ++i )
 {
  E01 = hits[ i ].fFirstHit->getEmissionEnergy();
  dE1 = hits[ i ].fFirstHit->getEnergyDeposition();
  h1EnergyDepositionAcceptedBeforeCuts->Fill( dE1 );
  h1EnergyDepositionAcceptedBeforeCutsFirstScattering->Fill( dE1 );

  if ( fPromptInData && TMath::Abs( E01 - fPromptEnergy) < 0.0001 )
  {
    if ( !( dE1 > fPromptEnergyThreshold ) )
     return;
  }
  else if ( !( dE1 > fEnergyThreshold ) )
  {
   return;
  }
 } 


///////


 for ( unsigned int i = 0; i < fNumberOfGammasGeneratedPerEvent; ++i )
 {
  E02 = hits[ i ].fSecondHit->getEmissionEnergy();
  dE2 = hits[ i ].fSecondHit->getEnergyDeposition();
  h1EnergyDepositionAcceptedBeforeCuts->Fill( dE2 );
  h1EnergyDepositionAcceptedBeforeCutsSecondScattering->Fill( dE2 );

  if ( fPromptInData && TMath::Abs( E02 - fPromptEnergy) < 0.0001 )
  {
    if ( !( dE2 > fPromptEnergyThreshold ) )
     return;
  }
  else if ( !( dE2 > fEnergyThreshold ) )
  {
   return;
  }
 }


//////

 ++fNumberOfDetectedEvents; 
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

 for ( std::vector<TwoHits>::iterator it = hits.begin(); it != hits.end(); ++it )
 {
  TVector3 v = it->fFirstHit->getHitPosition();

  h2XYHitPositionAccepted->Fill( v.x(), v.y() );
  h2XZHitPositionAccepted->Fill( v.x(), v.z() );
  h2YZHitPositionAccepted->Fill( v.y(), v.z() );
  h1EnergyDepositionAcceptedAfterCuts->Fill( it->fFirstHit->getEnergyDeposition() );
  h1GammaEnergyAccepted->Fill( it->fFirstHit->getEnergy() );
  h1EnergyDepositionAcceptedAfterCutsFirstScattering->Fill( it->fFirstHit->getEnergyDeposition() );

  v = it->fSecondHit->getHitPosition();

  h2XYHitPositionAccepted->Fill( v.x(), v.y() );
  h2XZHitPositionAccepted->Fill( v.x(), v.z() );
  h2YZHitPositionAccepted->Fill( v.y(), v.z() );
  h1EnergyDepositionAcceptedAfterCuts->Fill( it->fSecondHit->getEnergyDeposition() );
  h1GammaEnergyAccepted->Fill( it->fSecondHit->getEnergy() );
  h1EnergyDepositionAcceptedAfterCutsSecondScattering->Fill( it->fSecondHit->getEnergyDeposition() );

 }

}
