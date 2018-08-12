#include <iostream>
#include "REDataCreator.h"
#include "TVector3.h"
#include "TMath.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class read raw data from simulation and convert them to format useful for analysis
File: REDataCreator.cpp
**/

REDataCreator::REDataCreator() { fGenerator.initGenerator(); }

REDataCreator::~REDataCreator() {}

void REDataCreator::extractDataFromEntry()
{
 if ( kUseSmearingEnergyDeposition )
  fData.setEnergyDeposition( getSmearedEnergyDeposition( fReader->getEnergyLossDuringProcess() ) );
 else
  fData.setEnergyDeposition( fReader->getEnergyLossDuringProcess() );

 int eventID = fReader->getEventID();
 int trackID = fReader->getTrackID();

 if ( fCurrentEventID != eventID )
 {
  fCurrentEventID = eventID;
  fCurrentTrackID = trackID;
  fCurrentScattersPerTrackIndex = 1;
 }
 else if ( fCurrentTrackID != trackID )
 {
  fCurrentTrackID = trackID;
  fCurrentScattersPerTrackIndex = 1;  
 }
 else
 {
  ++fCurrentScattersPerTrackIndex;
 }

 fData.setEventID( eventID );
 fData.setTrackID( trackID);
 fData.setScatteringIndex( fCurrentScattersPerTrackIndex );
 
 TVector3 hit_position = fReader->getProcessPosition() * 0.1; //conversion from milimeters to centimeters
 TVector3 sci_position = fReader->getScintilatorPosition() * 0.1; //conversion from milimeters to centimeters

 TVector3 new_hit_position;
 
 if ( kUseSmearingZ )
  new_hit_position = TVector3( sci_position.x(), sci_position.y(), getSmearedZ( hit_position.z() ) );
 else
  new_hit_position = TVector3( sci_position.x(), sci_position.y(), hit_position.z() );

 fData.setHitPosition( new_hit_position );
 fData.setScintilatorPosition( sci_position );

 if ( kUseSmearingTime )
  fData.setTime( getSmearedTime( fReader->getGlobalTime() ) );
 else
  fData.setTime( fReader->getGlobalTime() );

 double corrected_time = fData.getTime() - fData.getHitPosition().Mag()/kLightVelocityInVaccum;
 fData.setCorrectedTime( corrected_time );
}

ToolsForAnalysis::AnalysisData* REDataCreator::getData() { return &fData; }

void REDataCreator::setReader( ToolsForGATE::GlobalActorReader* reader ) { fReader = reader; }

void REDataCreator::setSigmaZ( double sigma ) { fSigmaZ = sigma; }

void REDataCreator::setSigmaTime( double sigma ) { fSigmaTime = sigma; }

void REDataCreator::useSmearingZ( bool use ) { kUseSmearingZ = use; }

void REDataCreator::useSmearingTime( bool use ) { kUseSmearingTime = use; }

void REDataCreator::useSmearingEnergyDeposition( bool use ) { kUseSmearingEnergyDeposition = use; }

void REDataCreator::setNormalDistributionRange( double xmin, double xmax )
{ 
 fRangeMin = xmin;
 fRangeMax = xmax;
 fIsRangeON = true;
 fGenerator.setRangeForNormalDistribution( fRangeMin, fRangeMin ); 
}

void REDataCreator::setSeed( unsigned int seed ) 
{
 fSeed = seed; 
 fGenerator.setSeed( fSeed ); 
}

double REDataCreator::getSmearedZ( double z ) { return fGenerator.getValueFromNormalDistribution( z, fSigmaZ ); }

double REDataCreator::getSmearedEnergyDeposition( double energy ) { return fGenerator.getValueFromNormalDistribution( energy, calcSigmaEnergy( energy ) ); }

double REDataCreator::getSmearedTime( double time ) {  return fGenerator.getValueFromNormalDistribution( time, fSigmaTime ); }
  
//Below: In Sqrt we divide energy by 1000 beacouse energy unit is keV and we need here energy in MeV
double REDataCreator::calcSigmaEnergy( double energy ) { return ( 0.044 * energy ) / TMath::Sqrt( energy / 1000.0 ); } 

void REDataCreator::displayStatus()
{
 std::cout << "*****************************************************" << std::endl;
 std::cout << " STATUS OF: REDataCreator " << std::endl;
 std::cout << " fReader = " << fReader << std::endl;
 std::cout << " fSigmaZ = " << fSigmaZ << std::endl;
 std::cout << " fSigmaTime = " << fSigmaTime << std::endl;
 std::cout << " kUseSmearingZ = " << kUseSmearingZ << std::endl;
 std::cout << " kUseSmearingTime = " << kUseSmearingTime << std::endl;
 std::cout << " kUseSmearingEnergyDeposition = " << kUseSmearingEnergyDeposition << std::endl; 
 std::cout << " fRangeMin = " << fRangeMin << " fRangeMax = " << fRangeMax << " fIsRangeON = " << fIsRangeON << std::endl;
 std::cout << " fSeed = " << fSeed << std::endl;
 std::cout << "*****************************************************" << std::endl;
}
