#include <iostream>
#include "DPDataCreator.h"
#include "TVector3.h"
#include "TMath.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class read raw data from simulation and convert them to format useful for analysis
File: DPDataCreator.cpp
**/

DPDataCreator::DPDataCreator() { fGenerator.initGenerator(); }

DPDataCreator::~DPDataCreator() {}

void DPDataCreator::extractDataFromEntry()
{
 if ( isJobFinished() )
 {
  fReader->stopJob();
  return;
 }

 fData.setEnergyDeposition( getSmearedEnergy( fReader->getEnergyLossDuringProcess() ) );

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

 fData.setHitPosition( fReader->getProcessPosition() * 0.1 ); //conversion from milimeters to centimeters
 fData.setScintilatorPosition( fReader->getScintilatorPosition() * 0.1 ); //conversion from milimeters to centimeters

 fData.setTime( fReader->getGlobalTime() );

 fData.setEnergy( fReader->getEnergyBeforeProcess() );

 fData.setEmissionEnergy( fReader->getEmissionEnergyFromSource() );

}

ToolsForAnalysis::AnalysisData* DPDataCreator::getData() { return &fData; }

void DPDataCreator::setReader( ToolsForGATE::GlobalActorReader* reader ) { fReader = reader; }

double DPDataCreator::getSmearedEnergy( double energy_keV ) { return fGenerator.getValueFromNormalDistribution( energy_keV, calcSigmaEnergy( energy_keV ) ); }

double DPDataCreator::calcSigmaEnergy( double energy_keV ) { return ( 0.044 * energy_keV ) / TMath::Sqrt( energy_keV / 1000.0 ); } 
