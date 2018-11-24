/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file Event.h
 */

#ifndef EVENT_H 
#define EVENT_H 
#include <TObject.h>
#include <string>
#include <vector>
#include <TVector3.h>

class JPetGATETrackInteraction : public TObject {
public:
  JPetGATETrackInteraction();
  double fEnergyBeforeProcess = -1;//keV
  double fEnergyDeposition = -1;//keV
  double fLocalTime = -1;//ps
  //double fGlobalTime = -1;
  TVector3 fHitPosition;//cm
  TVector3 fVolumeCenter;//cm
  TVector3 fPolarizationBeforeProcess;
  TVector3 fMomentumBeforeProcess;
  std::string fVolumeName;

  TVector3 getScintilatorPosition(){ return fVolumeCenter; }
  TVector3 getHitPosition(){ return fHitPosition; }
  double getEneDepos() { return fEnergyDeposition; }
  double getTime() { return fLocalTime; }
  TVector3 getPolarizationIn(){ return fPolarizationBeforeProcess; }
  TVector3 getMomentumIn(){ return fMomentumBeforeProcess; }

  ClassDef(JPetGATETrackInteraction,1)
};

class JPetGATETrack : public TObject {
public:
  JPetGATETrack();
  int fTrackID = -1;
  double fEmissionEnergy = -1;
  std::vector<JPetGATETrackInteraction> fTrackInteractions;
  ClassDef(JPetGATETrack,1)
};


class JPetGATEEvent: public TObject {
public:
  JPetGATEEvent();
  int fEventID = -1;
  std::vector<JPetGATETrack> fTracks;
  ClassDef(JPetGATEEvent,1)
};
#endif /*  !EVENT_H */
