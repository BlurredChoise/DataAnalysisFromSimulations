#ifndef UnpackingModule_h
#define UnpackingModule_h

#include <TObject.h>
#include <iostream>
#include <string>
#include <map>
#include "Event.h"
#include <sstream>

class UnpackingModule : public TObject {

private:
  std::string boardType;
  std::string boardAddress;
  std::string hubAddress;
  int channelNumber;
  int channelOffset;
  int resolution;
  std::string measurementType;
  size_t entireEventSize;
  
  bool invertBytes;
  
  std::map<std::string, UnpackingModule*> internalUnpackers;
 
public:
  
  UnpackingModule() {}
  UnpackingModule(std::string bT, std::string bA, std::string hA, int cN, int o, int r, std::string mR, bool dec, bool dbg);
  ~UnpackingModule() {}
  
  void AddUnpacker(std::string s, UnpackingModule* u) { internalUnpackers[s] = u; }
  UnpackingModule* GetUnpacker(std::string s) { 
    if (internalUnpackers.count(s) == 1)
      return internalUnpackers[s];
    else
      return NULL;
  }
  
  void SetBoardType(std::string t) { boardType = t; }
  void SetBoardAddress(std::string t) { boardAddress = t; }
  void SetHubAddress(std::string t) { hubAddress = t; }
  void SetChannelNumber(int t) { channelNumber = t; }
  void SetResolution(int t) { resolution = t; }
  void SetMeasurementType(std::string t) { measurementType = t; }
  void SetInvertBytes(bool dec) { invertBytes = dec; }
  void SetEntireEventSize(size_t s) { entireEventSize = s; }
  
  std::string GetBoardType() { return boardType; }
  std::string GetBoardAddress() { return boardAddress; }
  std::string GetHubAddress() { return hubAddress; }
  int GetChannelNumber() { return channelNumber; }
  int GetChannelOffset() { return channelOffset; }
  int GetResolution() { return resolution; }
  std::string GetMeasurementType() { return measurementType; }
  bool GetInvertBytes() { return invertBytes; }
  size_t GetEntireEventSize() { return entireEventSize; }
  
  virtual void ProcessEvent(UInt_t* data);
  virtual void ProcessEvent(UInt_t* data, Event* evt);
  
  virtual void GetADCHits();
  virtual void GetTDCHits();
  
  virtual void SayHi();
  
  virtual void Clear();
 
  std::string UIntToString(UInt_t t);
  
  std::map<std::string, UnpackingModule*>::iterator GetInternalUnpackersIterBegin() { return internalUnpackers.begin(); }
  std::map<std::string, UnpackingModule*>::iterator GetInternalUnpackersIterEnd() { return internalUnpackers.end(); }


  // part of Lattice_TDC unpacking interface
  virtual int GetLeadMult(int /*channel*/) { return -1; }
  virtual int GetLeadFineTime(int /*channel*/, int /*mult*/) { return -1; }
  virtual int GetLeadCoarseTime(int /*channel*/, int /*mult*/) { return -1; }
  virtual int GetLeadEpoch(int /*channel*/, int /*mult*/) { return -1; }

  virtual int GetTrailMult(int /*channel*/) { return -1; }
  virtual int GetTrailFineTime(int /*channel*/, int /*mult*/) { return -1; }
  virtual int GetTrailCoarseTime(int /*channel*/, int /*mult*/) { return -1; }
  virtual int GetTrailEpoch(int /*channel*/, int /*mult*/) { return -1; }

  virtual void SetReferenceChannel(int /*t*/) {}
  virtual UInt_t GetErrorBits() { return -1; }


  // part of ADC unpacking interface
  virtual Int_t GetSample(Int_t /*channel*/, Int_t /*sampleNr*/) {return -1; }
  virtual Int_t GetDspSum(Int_t /*channel*/) {return -1; }
  virtual Int_t GetDspMean(Int_t /*channel*/) {return -1; }
  virtual Int_t GetDspCfA(Int_t /*channel*/) {return -1; }
  virtual Int_t GetDspCfB(Int_t /*channel*/) {return -1; }
  virtual Int_t GetDspCfT(Int_t /*channel*/) {return -1; }
  virtual Int_t GetNumberOfSamples() {return -1; }
 
  UInt_t ReverseHex(UInt_t n);
  
  bool debugMode;
  
};


#endif
