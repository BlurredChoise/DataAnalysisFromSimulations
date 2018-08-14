#include <iostream>
#include "REAnalysis.h"
#include "../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../Tools/ToolsForROOT/ReadAndSave.h"
#include "TFile.h"
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class perform analysis of data from simulation
File: REAnalysis_StandardMethods.cpp
**/

REAnalysis::REAnalysis() 
{ 
 fGenerator.initGenerator();
 initHistograms(); 
 fHits.resize(3);
 fHits[ 0 ] = nullptr;
 fHits[ 1 ] = nullptr;
 fHits[ 2 ] = nullptr;
 fCounters = std::vector<unsigned int>(7,0);
}

REAnalysis::~REAnalysis()
{
 if ( !kHistogramsSaved )
  deleteHistograms();
}

void REAnalysis::analyzeEntry()
{
 REData data = *( dynamic_cast< REData* >( fCreator->getData() ) );
 if ( data.getEventID() != fEventID )
 {
  analyzeDataSet();
  fEventID = data.getEventID();
  fDatas.clear();
  fHits[ 0 ] = nullptr;
  fHits[ 1 ] = nullptr;
  fHits[ 2 ] = nullptr;
 }
 fDatas.push_back( data );
}

void REAnalysis::setCreator( REDataCreator* creator ) { fCreator = creator; }

void REAnalysis::setSigmaEnergyThreshold( double sigma ) { fSigmaEnergyThreshold = sigma; }

void REAnalysis::setMeanEnergyThreshold( double mean ) { fMeanEnergyThreshold = mean; }

void REAnalysis::useSmearingEnergyThreshold( bool use ) { kUseSmearingEnergyThreshold = use; }

void REAnalysis::setNormalDistributionRange( double xmin, double xmax )
{ 
 fGenerator.setRangeForNormalDistribution( xmin, xmax );
 fRangeMin = xmin;
 fRangeMax = xmax; 
 fIsRangeON = true;
}

void REAnalysis::useHitsSeparationByTime( bool use ) { kUseHitsSeparationByTime = use; }

void REAnalysis::setSeed( unsigned int seed ) 
{ 
 fSeed = seed;
 fGenerator.setSeed( fSeed ); 
}

double REAnalysis::getSmearedEnergyThreshold() { return fGenerator.getValueFromNormalDistributionInRange( fMeanEnergyThreshold, fSigmaEnergyThreshold ); }

void REAnalysis::displayStatus()
{
 std::cout << "*****************************************************" << std::endl;
 std::cout << " STATUS OF: REAnalysis " << std::endl;
 std::cout << " fCreator = " << fCreator << std::endl;
 std::cout << " fSigmaEnergyThreshold = " << fSigmaEnergyThreshold << std::endl;
 std::cout << " fMeanEnergyThreshold = " << fMeanEnergyThreshold << std::endl;
 std::cout << " kUseSmearingEnergyThreshold = " << kUseSmearingEnergyThreshold << std::endl;
 std::cout << " fRangeMin = " << fRangeMin << " fRangeMax = " << fRangeMax << " fIsRangeON = " << fIsRangeON << std::endl;
 std::cout << " kUseHitsSeparationByTime = " << kUseHitsSeparationByTime << std::endl;
 std::cout << " fSeed = " << fSeed << std::endl;
 std::cout << " fEnergyThreshold = " << fEnergyThreshold << std::endl;
 std::cout << "*****************************************************" << std::endl;
}

void REAnalysis::saveHistograms( std::string output_file_name )
{
 TFile* file = ToolsForROOT::ReadAndSave::createFile( output_file_name, true );
 if ( !file )
  return;
 else
  kHistogramsSaved = true;
  
 std::cout << "Saving histograms .. " << std::endl;
 ToolsForROOT::ReadAndSave::saveToFile( file, fH1EnergyDeposition );
 ToolsForROOT::ReadAndSave::saveToFile( file, fH1TrueTheta );
 ToolsForROOT::ReadAndSave::saveToFile( file, fH1FakeTheta );
 ToolsForROOT::ReadAndSave::saveToFile( file, fH1TrueAndFakeTheta );
 ToolsForROOT::ReadAndSave::saveToFile( file, fH1EnergyDepositionFromTheta );
 
 ToolsForROOT::ReadAndSave::closeFile( file );

 for ( int i = 0; i < fCounters.size(); ++i )
  std::cout << "Counter no. " << i << " value = " << fCounters[ i ] << std::endl;
}

void REAnalysis::initHistograms()
{
 fH1EnergyDeposition = ToolsForROOT::HistogramsCreator::getTH1F( "fH1EnergyDeposition",  351 * 4, -0.5, 350.5, "#Delta E [keV]", "Counts" ); 
 fH1TrueTheta = ToolsForROOT::HistogramsCreator::getTH1F( "fH1TrueTheta", 180, -0.5, 180.5, "#theta_{True} [deg]", "Counts" );
 fH1FakeTheta = ToolsForROOT::HistogramsCreator::getTH1F( "fH1FakeTheta", 180, -0.5, 180.5, "#theta_{Fake} [deg]", "Counts" );
 fH1TrueAndFakeTheta = ToolsForROOT::HistogramsCreator::getTH1F( "fH1TrueAndFakeTheta", 180, -0.5, 180.5, "#theta_{True} and #theta_{Fake} [deg]", "Counts" );
 fH1EnergyDepositionFromTheta = ToolsForROOT::HistogramsCreator::getTH1F( "fH1EnergyDepositionFromTheta",  351 * 4, -0.5, 350.5, "#Delta E [keV]", "Counts" );
}

void REAnalysis::deleteHistograms()
{
 delete fH1EnergyDeposition;
 delete fH1TrueTheta;
 delete fH1FakeTheta;
 delete fH1TrueAndFakeTheta;
}
