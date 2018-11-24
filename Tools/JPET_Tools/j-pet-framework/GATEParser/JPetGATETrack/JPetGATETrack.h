
#ifndef JPetGATETrack_h
#define JPetGATETrack_h 
#include <TObject.h>
#include <string>
#include <vector>
#include <JPetGATETrackInteraction/JPetGATETrackInteraction.h>

class JPetGATETrack : public TObject {
public:
  JPetGATETrack();
  int fTrackID = -1;
  double fEmissionEnergy = -1;
  std::vector<JPetGATETrackInteraction> fTrackInteractions;
  ClassDef(JPetGATETrack,1)
};

#endif 
