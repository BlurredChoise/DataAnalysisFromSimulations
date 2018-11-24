#include <iostream>
#include "Event.h"

using namespace std;

ClassImp(Event);

Event::Event() {   
  TDCHits = new TClonesArray("TDCHitExtended", 2100);
  
  TDCHits->Clear("C");
  
  totalNTDCHits = 0;
  
  TDCReferenceTime = 0;
  
  errorBits = 0;
}

TDCHit* Event::AddTDCHit(int channel) {
  //cerr<<"Event: adding TDC hit on channel "<<channel<<endl;
  TClonesArray& thits = *TDCHits;
  TDCHit* hit = dynamic_cast<TDCHit*>(thits.ConstructedAt(totalNTDCHits++)); 
  hit->SetChannel(channel);
  return hit;
}

TDCHitExtended* Event::AddTDCHitExtended(int channel) {
  //cerr<<"Event: adding TDC hit on channel "<<channel<<endl;
  TClonesArray& thits = *TDCHits;
  TDCHitExtended* hit = dynamic_cast<TDCHitExtended*>(thits.ConstructedAt(totalNTDCHits++)); 
  hit->SetChannel(channel);
  return hit;
}


void Event::Clear(void) {  
  TDCHits->Clear("C");
  
  totalNTDCHits = 0;
  
  TDCReferenceTime = 0;
}
