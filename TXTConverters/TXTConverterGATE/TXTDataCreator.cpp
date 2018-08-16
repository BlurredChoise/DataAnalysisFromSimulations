#include <iostream>
#include "TXTDataCreator.h"
#include "TVector3.h"
#include "TMath.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class read raw data from simulation and convert them to format useful for analysis
File: TXTDataCreator.cpp
**/

TXTDataCreator::TXTDataCreator() {}

TXTDataCreator::~TXTDataCreator() {}

void TXTDataCreator::extractDataFromEntry()
{
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

 fData.setHitPosition( fReader->getProcessPosition() * 0.1 ); //conversion from milimeters to centimeters
 fData.setScintilatorPosition( fReader->getScintilatorPosition() * 0.1 ); //conversion from milimeters to centimeters

 fData.setTime( fReader->getGlobalTime() );
}

ToolsForAnalysis::AnalysisData* TXTDataCreator::getData() { return &fData; }

void TXTDataCreator::setReader( ToolsForGATE::GlobalActorReader* reader ) { fReader = reader; }
