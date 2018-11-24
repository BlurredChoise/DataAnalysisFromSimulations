#ifndef Unpacker2_h
#define Unpacker2_h

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TObjectTable.h>
#include <TH1F.h>
#include <string>
#include "UnpackingModule.h"
#include "Event.h"
#include "EventIII.h"
#include <map>

#define REF_CHANNELS_NUMBER 50

class Unpacker2 : public TObject {
  
private:
  
  std::map<std::string, UnpackingModule*> unpackers;
  
  int eventsToAnalyze;
  
  size_t reverseHex(size_t n);

  bool areBytesToBeInverted(std::string);
  bool invertBytes;
  bool fullSetup;
  
  bool debugMode;
  
  long int fileSize;

  // stuff for "calculate_times"
  TClonesArray* pArray = 0;
  TIter * iter;
  TDCHit* pHit = 0;
  int refTimeEpoch[REF_CHANNELS_NUMBER];
  int refTimeCoarse[REF_CHANNELS_NUMBER];
  int refTimeFine[REF_CHANNELS_NUMBER];
  int refChannelOffset;
  TH1F * calibHist;
  
public:

  Unpacker2();
  Unpacker2(const char* hldFile, const char* configFile, int numberOfEvents);
  ~Unpacker2() {}

  void Init();
  void UnpackSingleStep(const char* hldFile, const char* configFile, int numberOfEvents,
			int refChannelOffset, const char* calibFile);
  
  bool calculateTimes(Event * old_event, Event * new_event);
  bool calculateHits(Event * evt_in, EventIII * evt_out);
  
  TH1F * loadCalibHisto(const char* calibFile);
  
  void ParseConfigFile(std::string f, std::string s);
  void DistributeEvents(std::string f);
  void DistributeEventsSingleStep(std::string file);
  
  void AddUnpacker(std::string s, UnpackingModule* u) { unpackers[s] = u; }
  UnpackingModule* GetUnpacker(std::string s) { return unpackers[s]; }
  
  struct EventHdr {
    UInt_t fullSize;
    UInt_t decoding;
    UInt_t id;
    UInt_t seqNr;
    UInt_t date;
    UInt_t time;
    UInt_t runNr;
    UInt_t pad;
  } hdr;
  
  struct SubEventHdr {
    UInt_t size;
    UInt_t decoding;
    UInt_t hubAddress;
    UInt_t trgNr;
  } subHdr;
  
  UInt_t* pHdr;
  UInt_t* subPHdr;
  
  size_t getSubHdrSize()    const { return sizeof(SubEventHdr); }
  size_t getHdrSize()    const { return sizeof(EventHdr); }
  UInt_t getFullSize()   const { return ((EventHdr*)pHdr)->fullSize; }
  size_t getDataSize();
  std::string getHubAddress();
  size_t getDataLen()    const { return ((getFullSize() - getHdrSize()) + 3) / 4; }
  size_t align8(const size_t i) const { return 8 * size_t((i - 1) / 8 + 1); }
  size_t getPaddedSize() { return align8(getDataSize()); }
  size_t getPaddedEventSize() { return align8(getFullSize()); }
  
  size_t ReverseHex(size_t n);
    
};



#endif
