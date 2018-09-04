#include "DPData.h"
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class represent data for analysis
File: DPData.cpp
**/

DPData::DPData() {}

DPData::~DPData() {}

void DPData::setEnergyDeposition( const double& energy ) { fEnergyDeposition = energy; }

double DPData::getEnergyDeposition() const { return fEnergyDeposition; }

void DPData::setEventID( const int& eventID ) { fEventID = eventID; }

int DPData::getEventID() const { return fEventID; }

void DPData::setTrackID( const int& trackID ) { fTrackID = trackID; }

int DPData::getTrackID() const { return fTrackID; }

void DPData::setHitPosition( const TVector3& hit_position ) { fHitPosition = hit_position; }

TVector3 DPData::getHitPosition() const { return fHitPosition; }

void DPData::setScintilatorPosition( const TVector3& sci_position ) { fScintilatorPosition = sci_position; }

TVector3 DPData::getScintilatorPosition() const { return fScintilatorPosition; }

void DPData::setTime( const double& time ) { fTime = time; }

double DPData::getTime() const { return fTime; }

void DPData::setScatteringIndex( const unsigned int index ) { fScatteringIndex = index; }

unsigned int DPData::getScatteringIndex() const { return fScatteringIndex; }

void DPData::setEnergy( const double& energy) { fEnergy = energy; }

double DPData::getEnergy() const { return fEnergy; }

void DPData::setEmissionEnergy( const double& energy) { fEmissionEnergy = energy; }

double DPData::getEmissionEnergy() const { return fEmissionEnergy; }
