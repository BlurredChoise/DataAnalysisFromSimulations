#include "TDCHitIII.h"

using namespace std;

ClassImp(TDCHitIII);

TDCHitIII::TDCHitIII() {
  channel = -1;

	leadTime = -100000;
	trailTime = -100000;
	tot = -100000;
	referenceDiff = -100000;
}

TDCHitIII::~TDCHitIII() {
}
