#ifndef Unpacker_TRB3_h
#define Unpacker_TRB3_h

#include "UnpackingModule.h"

class Unpacker_TRB3 : public UnpackingModule {
  
private:
  Event* event;
  int referenceChannel;
  
public:
  
  Unpacker_TRB3() {}
  Unpacker_TRB3(std::string bT, std::string bA, std::string hA, int cN, int o, int r, std::string mR, bool dec, bool dbg);
  ~Unpacker_TRB3() {}
  
  void ProcessEvent(UInt_t* data, Event* evt);
  
//  void GetADCHits();
  void GetTDCHits();
  
  void SetReferenceChannel(int t) { referenceChannel = t; }
  
  void SayHi() { std::cerr<<"Hi from TRB3"<<std::endl; }
  
  void Clear() {}
  
};

#endif
