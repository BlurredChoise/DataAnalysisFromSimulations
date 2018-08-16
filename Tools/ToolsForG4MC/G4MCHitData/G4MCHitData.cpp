#include "G4MCHitData.h"
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class represent data for analysis
File: G4MCHitData.cpp
**/

namespace ToolsForG4MC
{

 G4MCHitData::G4MCHitData() {}

 G4MCHitData::~G4MCHitData() {}

 void G4MCHitData::setEnergyDeposition( const double& energy ) { fEnergyDeposition = energy; }

 double G4MCHitData::getEnergyDeposition() const { return fEnergyDeposition; }

 void G4MCHitData::setEventID( const int& eventID ) { fEventID = eventID; }

 int G4MCHitData::getEventID() const { return fEventID; }

 void G4MCHitData::setTrackID( const int& trackID ) { fTrackID = trackID; }

 int G4MCHitData::getTrackID() const { return fTrackID; }

 void G4MCHitData::setHitPosition( const TVector3& hit_position ) { fHitPosition = hit_position; }

 TVector3 G4MCHitData::getHitPosition() const { return fHitPosition; }

 void G4MCHitData::setScintilatorPosition( const TVector3& sci_position ) { fScintilatorPosition = sci_position; }

 TVector3 G4MCHitData::getScintilatorPosition() const { return fScintilatorPosition; }

 void G4MCHitData::setTime( const double& time ) { fTime = time; }

 double G4MCHitData::getTime() const { return fTime; }

 void G4MCHitData::setScatteringIndex( const unsigned int index ) { fScatteringIndex = index; }

 unsigned int G4MCHitData::getScatteringIndex() const { return fScatteringIndex; }

 void G4MCHitData::setGammaKind( G4MCHitData::GammaKind kind ) { fGammaKind = kind; }
 
 G4MCHitData::GammaKind G4MCHitData::getGammaKind() const { return fGammaKind; }

};

