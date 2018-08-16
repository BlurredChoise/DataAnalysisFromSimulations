#ifndef ThreeHitsEventsOnlyModel_h
#define ThreeHitsEventsOnlyModel_h
#include "TXTModel.h"
#include "TH1F.h"
#include "TH2F.h"

class ThreeHitsEventsOnlyModel : public TXTModel
{
 public:
  ThreeHitsEventsOnlyModel();
  ~ThreeHitsEventsOnlyModel();

  virtual void saveControlHistograms();
  virtual void initControlHistograms();
  virtual void deleteControlHistograms();

  virtual void analyzeHitsSet( std::vector< ToolsForG4MC::G4MCHitData >* data );

 private:
  TH1F* h1EnergyDeposition;
  TH2F* h2HitPositionXY;
  TH2F* h2HitPositionXZ;
  TH2F* h2HitPositionYZ;
};

#endif
