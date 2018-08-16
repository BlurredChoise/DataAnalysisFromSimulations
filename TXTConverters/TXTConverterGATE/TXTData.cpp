#include "TXTData.h"
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class represent data for analysis
File: TXTData.cpp
**/

TXTData::TXTData() {}

TXTData::~TXTData() {}

void TXTData::setEnergyDeposition( const double& energy ) { fEnergyDeposition = energy; }

double TXTData::getEnergyDeposition() const { return fEnergyDeposition; }

void TXTData::setEventID( const int& eventID ) { fEventID = eventID; }

int TXTData::getEventID() const { return fEventID; }

void TXTData::setTrackID( const int& trackID ) { fTrackID = trackID; }

int TXTData::getTrackID() const { return fTrackID; }

void TXTData::setHitPosition( const TVector3& hit_position ) { fHitPosition = hit_position; }

TVector3 TXTData::getHitPosition() const { return fHitPosition; }

void TXTData::setScintilatorPosition( const TVector3& sci_position ) { fScintilatorPosition = sci_position; }

TVector3 TXTData::getScintilatorPosition() const { return fScintilatorPosition; }

void TXTData::setTime( const double& time ) { fTime = time; }

double TXTData::getTime() const { return fTime; }

void TXTData::setScatteringIndex( const unsigned int index ) { fScatteringIndex = index; }

unsigned int TXTData::getScatteringIndex() const { return fScatteringIndex; }
