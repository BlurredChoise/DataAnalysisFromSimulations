#include "TDCHit.h"
#include <iostream>

using namespace std;

ClassImp(TDCHit);

TDCHit::TDCHit() {
  channel = -1;

  leadsNum = 0;
  trailsNum = 0;
    
}

TDCHit::~TDCHit() {
}

void TDCHit::AddLeadTime(int fine, int coarse, int epoch) {
  leadFineTimes[leadsNum] = fine;
  leadCoarseTimes[leadsNum] = coarse;
  leadEpochs[leadsNum] = epoch;
  
  leadsNum++;
}

void TDCHit::AddTrailTime(int fine, int coarse, int epoch) {
  trailFineTimes[trailsNum] = fine;
  trailCoarseTimes[trailsNum] = coarse;
  trailEpochs[trailsNum] = epoch;
  
  trailsNum++;
}

void TDCHit::Clear(Option_t *){

  channel = -1;
  
  leadsNum = 0;
  trailsNum = 0;
  
}
