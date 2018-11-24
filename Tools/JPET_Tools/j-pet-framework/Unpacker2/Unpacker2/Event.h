#ifndef Event_h
#define Event_h

#include <fstream>
#include <TObject.h>
#include <TNamed.h>
#include <TClonesArray.h>
#include "TDCHit.h"
#include "TDCHitExtended.h"
#include <iostream>

class TDCHit;

class Event : public TNamed {
  
private:
  Int_t totalNTDCHits;
  float TDCReferenceTime;
  UInt_t errorBits;
  
public:
  TClonesArray* TDCHits;
  
  Event();
  virtual ~Event() { Clear(); }
  
  TDCHit* AddTDCHit(int channel);
  TDCHitExtended* AddTDCHitExtended(int channel);
  
  void SetTDCReferenceTime(float t) { TDCReferenceTime = t; }
  void SetErrorBits(UInt_t err) { errorBits = err; }
  
  Int_t GetTotalNTDCHits() { return totalNTDCHits; }
  float GetTDCReferenceTime() { return TDCReferenceTime; }
  UInt_t GetErrorBits() { return errorBits; }
  
  TClonesArray* GetTDCHitsArray() {return TDCHits;}
  
  void Clear(void);
  
  ClassDef(Event,1);
  
};


#endif
