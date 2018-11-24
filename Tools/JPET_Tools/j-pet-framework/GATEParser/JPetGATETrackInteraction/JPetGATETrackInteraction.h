#ifndef JPetGATETrackInteraction_H 
#define JPetGATETrackInteraction_H 
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

#endif
