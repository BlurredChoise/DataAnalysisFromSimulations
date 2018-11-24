#ifndef TDCHitIII_h
#define TDCHitIII_h

#include <fstream>
#include <TObject.h>
#include <TClonesArray.h>
#include <iostream>

class TDCHitIII : public TObject {
  
protected:
  Int_t channel;
	
	double leadTime;
	double trailTime;
	double tot;
	double referenceDiff;
  
public:

  TDCHitIII();
  ~TDCHitIII();
  
  void SetChannel(Int_t channel) { this->channel = channel; }
	int GetChannel() { return channel; }

	void SetLeadTime(double l) { this->leadTime = l; }
	double GetLeadTime() { return leadTime; }

	void SetTrailTime(double t) { this->trailTime = t; }
	double GetTrailTime() { return trailTime; }

	void SetTOT(double t) { this->tot = t; }
	double GetTOT() { return tot; }

	void SetReferenceDiff(double d) { this->referenceDiff = d; }
	double GetReferenceDiff() { return referenceDiff; }

  ClassDef(TDCHitIII,1);
};

#endif
