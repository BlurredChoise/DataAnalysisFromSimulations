#ifndef TDCChannel_h
#define TDCChannel_h

#include <fstream>
#include <TObject.h>
#include <TClonesArray.h>
#include <iostream>
#include <vector>

class TDCChannel : public TObject {

protected:
  Int_t channel;
  
  std::vector<double> leadTimes;
  std::vector<double> trailTimes;
  int hitsNum;

  
public:

  TDCChannel();
  ~TDCChannel();
  
  void SetChannel(Int_t channel) { this->channel = channel; }
  int GetChannel() { return channel; }
  int GetHitsNum() { return hitsNum; }
  
  void AddHit(double lead, double trail);

  double GetLeadTime(unsigned int mult) {
    return leadTimes[mult];
  }

  double GetTrailTime(unsigned int mult) {
    if( mult >= trailTimes.size() ){
      std::cout<<"asked for trail time out of range."<<std::endl;
      return 0.;
    }
    return trailTimes[mult];
  }

  int GetMult() { return hitsNum; }

  void Clear(Option_t * opt);
  
  ClassDef(TDCChannel,2);
};

#endif
