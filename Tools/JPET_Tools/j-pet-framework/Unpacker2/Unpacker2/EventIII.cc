#include <iostream>
#include "EventIII.h"

using namespace std;

ClassImp(EventIII);

EventIII::EventIII() : TNamed("EventIII", "EventIII") {   
  TDCChannels = new TClonesArray("TDCChannel", 2100);
  
  TDCChannels->Clear("C");
  
  totalNTDCChannels = 0;
}

TDCChannel* EventIII::AddTDCChannel(int channel) {
  TClonesArray& thits = *TDCChannels;
  TDCChannel* ch = dynamic_cast<TDCChannel*>(thits.ConstructedAt(totalNTDCChannels++));
  ch->SetChannel(channel);
  return ch;
}


void EventIII::Clear(void) {  
  TDCChannels->Clear("C");
  totalNTDCChannels = 0;
}
