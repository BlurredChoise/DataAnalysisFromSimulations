#include "REData.h"
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class represent data for analysis
File: REData.cpp
**/

REData::REData() {}

REData::~REData() {}

void REData::setEnergyDeposition( const double& energy ) { fEnergyDeposition = energy; }

double REData::getEnergyDeposition() const { return fEnergyDeposition; }

void REData::setEventID( const int& eventID ) { fEventID = eventID; }

int REData::getEventID() const { return fEventID; }

void REData::setTrackID( const int& trackID ) { fTrackID = trackID; }

int REData::getTrackID() const { return fTrackID; }

void REData::setHitPosition( const TVector3& hit_position ) { fHitPosition = hit_position; }

TVector3 REData::getHitPosition() const { return fHitPosition; }

void REData::setScintilatorPosition( const TVector3& sci_position ) { fScintilatorPosition = sci_position; }

TVector3 REData::getScintilatorPosition() const { return fScintilatorPosition; }

void REData::setTime( const double& time ) { fTime = time; }

double REData::getTime() const { return fTime; }

void REData::setCorrectedTime( const double& time ) { fCorrectedTime = time; }

double REData::getCorrectedTime() { return fCorrectedTime; }

void REData::setScatteringIndex( const unsigned int index ) { fScatteringIndex = index; }

unsigned int REData::getScatteringIndex() const { return fScatteringIndex; }
