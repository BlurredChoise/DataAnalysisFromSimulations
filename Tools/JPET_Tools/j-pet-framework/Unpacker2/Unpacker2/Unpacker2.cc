#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Unpacker2.h"
#include "Unpacker_TRB3.h"
#include "Unpacker_Lattice_TDC.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace std;

Unpacker2::Unpacker2(){
  Init();
}

Unpacker2::Unpacker2(const char* hldFile, const char* configFile, int numberOfEvents) {

  Init();

  eventsToAnalyze = numberOfEvents;

  //*** PARSING CONFIG FILE
  ParseConfigFile(string(hldFile), string(configFile));

  //*** READING BINARY DATA AND DISTRIBUTING IT TO APPROPRIATE UNPACKING MODULES
  DistributeEvents(string(hldFile));
}

void Unpacker2::Init(){
  debugMode = false;

  invertBytes = false;
  fullSetup = true;

  fileSize = 0;

}

void Unpacker2::UnpackSingleStep(const char* hldFile, const char* configFile, int numberOfEvents,
                                 int refChannelOffset, const char* calibFile){

  eventsToAnalyze = numberOfEvents;

  this->refChannelOffset = refChannelOffset;

  calibHist = loadCalibHisto(calibFile);

  //*** PARSING CONFIG FILE
  ParseConfigFile(string(hldFile), string(configFile));

  //*** READING BINARY DATA AND DISTRIBUTING IT TO APPROPRIATE UNPACKING MODULES
  DistributeEventsSingleStep(string(hldFile));

}

bool Unpacker2::areBytesToBeInverted(string f) {
  bool invert = false;
  // open the data file to check the byte ordering
  ifstream* file = new ifstream(f.c_str());

  if (file->is_open()) {

    // skip the file header
    file->ignore(32);

    // read out the header of the event into hdr structure
    pHdr = (UInt_t*) &hdr;
    file->read((char *) (pHdr), getHdrSize());
    subPHdr = (UInt_t*) &subHdr;
    file->read((char *) (subPHdr), getSubHdrSize());
    if(((SubEventHdr*)subPHdr)->decoding == 16777728) {
      invert = true;
    }

    // find the size of the file
    file->seekg(0, ios::end);
    fileSize = file->tellg();
  }
  file->close();
  return invert;
}

void Unpacker2::ParseConfigFile(string f, string s) {

  invertBytes = areBytesToBeInverted(f);

  // parsing xml config file
  boost::property_tree::ptree tree;

  try {
    boost::property_tree::read_xml(s, tree);
  } catch(boost::property_tree::xml_parser_error e) {
    cerr << "ERROR: Failed to read config file" << endl;
    exit(0);
  }

  // get the config options from the config file
  try {
    if (tree.get<string>("READOUT.DEBUG") == "ON") {
      debugMode = true;
    }
  } catch (exception e) {
    cerr << "ERROR: Incorrect config file structure" << endl;
    exit(0);
  }

  if (debugMode == true)
    cerr<<"DEBUG mode on"<<endl;

  // get the first data source entry in the config file
  boost::property_tree::ptree readoutTree = tree.get_child("READOUT");
  string type;
  string address;
  string hubAddress;
  string correctionFile;
  int channels = 0;
  int offset = 0;
  int resolution = 0;
  int referenceChannel = 0;
  string measurementType("");
  UnpackingModule* m;

  // iterate through entries and create appropriate unpackers
  for (const auto& readoutEntry : readoutTree) {
    // read out values from xml entry
    if ((readoutEntry.first) == "DATA_SOURCE") {
      type = (readoutEntry.second).get<string>("TYPE");
      address = (readoutEntry.second).get<string>("TRBNET_ADDRESS");
      hubAddress = (readoutEntry.second).get<string>("HUB_ADDRESS");
      referenceChannel = (readoutEntry.second).get<int>("REFERENCE_CHANNEL");
      correctionFile = (readoutEntry.second).get<string>("CORRECTION_FILE");


      if (type == "TRB3_S") {

        m = new Unpacker_TRB3(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode);
        m->SetReferenceChannel(referenceChannel);

        // create additional unpackers for internal modules
        boost::property_tree::ptree modulesTree = (readoutEntry.second).get_child("MODULES");
        for (const auto& module : modulesTree) {
          type = (module.second).get<string>("TYPE");
          address = (module.second).get<string>("TRBNET_ADDRESS");
          channels = (module.second).get<int>("NUMBER_OF_CHANNELS");
          offset = (module.second).get<int>("CHANNEL_OFFSET");
          resolution = (module.second).get<int>("RESOLUTION");
          measurementType = (module.second).get<string>("MEASUREMENT_TYPE");

          UnpackingModule* submodule = 0;
          if (type == "LATTICE_TDC") {
            submodule = new Unpacker_Lattice_TDC(type, address, hubAddress, channels, offset, resolution,
                                                 measurementType, invertBytes, debugMode, correctionFile);
          } else {
            submodule = new UnpackingModule(type, address, hubAddress, channels, offset, resolution,
                                            measurementType, invertBytes, debugMode);
          }
          m -> AddUnpacker(address, submodule);
        }
      } else { // default type
        m = new UnpackingModule(type, address, hubAddress, channels, offset, resolution, measurementType, invertBytes, debugMode);
        cerr << "  -- Creating UnpackingModule for unassigned type" << endl;
      }

      // add the module to the list
      AddUnpacker(hubAddress, m);

    }
  }
}

void Unpacker2::DistributeEvents(string f) {
  ifstream* file = new ifstream(f.c_str());

  if (file->is_open()) {

    // skip the file header
    file->ignore(32);

    int analyzedEvents = 0;

    Event* event = 0;

    // open a new file
    string newFileName = f + ".raw.root";
    TFile* newFile = new TFile(newFileName.c_str(), "RECREATE");
    TTree* newTree = new TTree("T", "Tree");
    Int_t split = 2;
    Int_t bsize = 64000;
    newTree->Branch("event", "Event", &event, bsize, split);

    cerr<<"Starting event loop"<<endl;

    event = new Event();

    size_t eventSize = 0;

    // iterate through all the events in the file
    while(true) {

      if(debugMode == true)
        cerr<<"Unpacker2.cc: Position in file at "<<file->tellg();

      // read out the header of the event into hdr structure
      pHdr = (UInt_t*) &hdr;
      file->read((char *) (pHdr), getHdrSize());

      eventSize = (size_t) getFullSize();

      if(debugMode == true)
        cerr<<" current event size "<<eventSize<<endl<<"Unpacker2.cc: Starting new event analysis, going over subevents"<<endl;


      if (eventSize == 32)
        continue;

      while(true) {
        subPHdr = (UInt_t*) &subHdr;
        file->read((char *) (subPHdr), getSubHdrSize());

        // read out the entire data of the event
        UInt_t* pData = new UInt_t[getDataSize()];
        file->read((char*) (pData), getDataSize());

        if(debugMode == true) {
          cerr<<"Unpacker2.cc: Subevent data size: "<<getDataSize()<<" starting with ";
          printf("%08X\n", (*pData));
          cerr<<"Unpacker2.cc: Subevent details: "<<((SubEventHdr*)subPHdr)->decoding<<" "<<((SubEventHdr*)subPHdr)->hubAddress<<" "<<((SubEventHdr*)subPHdr)->trgNr<<endl;
        }

        // call the unpacking module
        UnpackingModule* u = GetUnpacker(getHubAddress());
        if (u != NULL && (*pData) != 0) {
          if(debugMode == true)
            cerr<<"Unpacker2.cc: Processing event "<<analyzedEvents<<" on "<<getHubAddress()<<endl;
          GetUnpacker(getHubAddress())->SetEntireEventSize(getDataSize());
          GetUnpacker(getHubAddress())->ProcessEvent(pData, event);

          // gather decoded hits and fill them into event

          GetUnpacker(getHubAddress())->GetTDCHits();
//	  GetUnpacker(getHubAddress())->GetADCHits();
	
	}
	else if((*pData) == 0) {
	  cerr<<"WARNING: First data word empty, skipping event nr "<<analyzedEvents<<endl;
	}
	else if(u == NULL) {
	  cerr<<"ERROR: Unpacker not found for address: "<<getHubAddress()<<endl;
	  exit(1);
	}

	if(debugMode == true)
	  cerr<<"Unpacker2.cc: Ignoring "<<(getPaddedSize() - getDataSize())<<" bytes and reducing eventSize by "<<getDataSize(); 
	
	delete[] pData;
	
	// remove the padding bytes
	file->ignore(getPaddedSize() - getDataSize());
	
	eventSize -= getDataSize();
	
	if(debugMode == true)
	  cerr<<" leaving eventSize of "<<eventSize<<endl;
	
	if(eventSize <= 48 && fullSetup == false) { break; }
	
	eventSize -= getPaddedSize() - getDataSize();
	
	if((eventSize <= 64) && fullSetup == true) { break; }

	if((eventSize <= 176) && fullSetup == true) { break; }

      }

      newTree->Fill();

      if(analyzedEvents % 10000 == 0) {
        cerr<<analyzedEvents<<endl;
      }
      analyzedEvents++;

      event->Clear();

      if(debugMode == true) {
        cerr<<"Unpacker2.cc: Ignoring padding of the event "<<(align8(eventSize) - eventSize)<<endl;
        cerr<<"Unpacker2.cc: File pointer at "<<file->tellg()<<" of "<<fileSize<<" bytes"<<endl;
      }

      if (fullSetup == false) {
        file->ignore(align8(eventSize) - eventSize);
      }
      // check the end of loop conditions (end of file)
      if((fileSize - ((int)file->tellg())) < 500) { break; }
      if((file->eof() == true) || ((int)file->tellg() == fileSize)) { break; }
      if(analyzedEvents == eventsToAnalyze) { break; }
    }

    newFile->Write();

    delete newTree;
  }
  else { cerr<<"ERROR:failed to open data file"<<endl; }

  file->close();

  //*** END OF READING BINARY DATA
}


void Unpacker2::DistributeEventsSingleStep(string filename) {
  ifstream* file = new ifstream(filename.c_str());

  if (file->is_open()) {

    // skip the file header
    file->ignore(32);

    int analyzedEvents = 0;

    Event* event = 0;
    Event* eventII = 0;
    EventIII * eventIII = 0;

    // open a new file
    string newFileName = filename + ".root";
    TFile* newFile = new TFile(newFileName.c_str(), "RECREATE");
    TTree* newTree = new TTree("T", "Tree");
    Int_t split = 2;
    Int_t bsize = 64000;
    newTree->Branch("eventIII", "EventIII", &eventIII, bsize, split);

    cerr<<"Starting event loop"<<endl;

    event = new Event();
    eventII = new Event();
    eventIII = new EventIII();

    size_t eventSize = 0;

    // iterate through all the events in the file
    while(true) {

      if(debugMode == true)
        cerr<<"Unpacker2.cc: Position in file at "<<file->tellg();

      // read out the header of the event into hdr structure
      pHdr = (UInt_t*) &hdr;
      file->read((char *) (pHdr), getHdrSize());

      eventSize = (size_t) getFullSize();

      if(debugMode == true)
        cerr<<" current event size "<<eventSize<<endl<<"Unpacker2.cc: Starting new event analysis, going over subevents"<<endl;


      if (eventSize == 32)
        continue;

      while(true) {
        subPHdr = (UInt_t*) &subHdr;
        file->read((char *) (subPHdr), getSubHdrSize());

        // read out the entire data of the event
        UInt_t* pData = new UInt_t[getDataSize()];
        file->read((char*) (pData), getDataSize());

        if(debugMode == true) {
          cerr<<"Unpacker2.cc: Subevent data size: "<<getDataSize()<<" starting with ";
          printf("%08X\n", (*pData));
          cerr<<"Unpacker2.cc: Subevent details: "<<((SubEventHdr*)subPHdr)->decoding<<" "<<((SubEventHdr*)subPHdr)->hubAddress<<" "<<((SubEventHdr*)subPHdr)->trgNr<<endl;
        }

        // call the unpacking module
        UnpackingModule* u = GetUnpacker(getHubAddress());
        if (u != NULL && (*pData) != 0) {
          if(debugMode == true)
            cerr<<"Unpacker2.cc: Processing event "<<analyzedEvents<<" on "<<getHubAddress()<<endl;
          GetUnpacker(getHubAddress())->SetEntireEventSize(getDataSize());
          GetUnpacker(getHubAddress())->ProcessEvent(pData, event);

          // gather decoded hits and fill them into event

          GetUnpacker(getHubAddress())->GetTDCHits();
//	  GetUnpacker(getHubAddress())->GetADCHits();
	
	}
	else if((*pData) == 0) {
	  cerr<<"WARNING: First data word empty, skipping event nr "<<analyzedEvents<<endl;
	}
	else if(u == NULL) {
	  cerr<<"ERROR: Unpacker not found for address: "<<getHubAddress()<<endl;
	  exit(1);
	}

	if(debugMode == true)
	  cerr<<"Unpacker2.cc: Ignoring "<<(getPaddedSize() - getDataSize())<<" bytes and reducing eventSize by "<<getDataSize(); 
	
	delete[] pData;
	
	// remove the padding bytes
	file->ignore(getPaddedSize() - getDataSize());
	
	eventSize -= getDataSize();
	
	if(debugMode == true)
	  cerr<<" leaving eventSize of "<<eventSize<<endl;
	
	if(eventSize <= 48 && fullSetup == false) { break; }
	
	eventSize -= getPaddedSize() - getDataSize();
	
	if((eventSize <= 64) && fullSetup == true) { break; }

	if((eventSize <= 176) && fullSetup == true) { break; }

      }

      // perform the actions from former "calculate_times" separate step
      if ( !calculateTimes(event, eventII) ){
        continue;
      }

      // perform the actions from former "calculate_hits" separate step
      if( !calculateHits(eventII, eventIII) ){
        continue;
      }

      newTree->Fill();

      if(analyzedEvents % 10000 == 0) {
        cerr<<analyzedEvents<<endl;
      }

      analyzedEvents++;

      event->Clear();
      eventII->Clear();
      eventIII->Clear();

      if(debugMode == true) {
        cerr<<"Unpacker2.cc: Ignoring padding of the event "<<(align8(eventSize) - eventSize)<<endl;
        cerr<<"Unpacker2.cc: File pointer at "<<file->tellg()<<" of "<<fileSize<<" bytes"<<endl;
      }

      if (fullSetup == false) {
        file->ignore(align8(eventSize) - eventSize);
      }
      // check the end of loop conditions (end of file)
      if((fileSize - ((int)file->tellg())) < 500) { break; }
      if((file->eof() == true) || ((int)file->tellg() == fileSize)) { break; }
      if(analyzedEvents == eventsToAnalyze) { break; }
    }

    newFile->Write();

    delete newTree;
  }
  else { cerr<<"ERROR:failed to open data file"<<endl; }

  file->close();

  //*** END OF READING BINARY DATA
}

TH1F * Unpacker2::loadCalibHisto(const char * calibFile){

  TH1F * tmp;
  TH1F * returnHisto;

  // load zero offsets in case no file is specified
  string calibFileName = string(calibFile);
  if (calibFileName.find(".root") == string::npos) {
    returnHisto = new TH1F("stretcher_offsets", "stretcher_offsets", REF_CHANNELS_NUMBER * refChannelOffset, 0, REF_CHANNELS_NUMBER * refChannelOffset);
    for (int i = 0; i < REF_CHANNELS_NUMBER * refChannelOffset; i++) {
      returnHisto->SetBinContent(i + 1, 0);
    }
    cerr<<"Zero offsets and calib loaded"<<endl;
  }
    // load the stretcher offsets calibration
  else {
    TFile* file = new TFile();
    ifstream my_file(calibFileName.c_str());
    file = new TFile(calibFileName.c_str(), "READ");
    TDirectory* dir = gDirectory->GetDirectory("Rint:/");
    tmp = (TH1F*)file->Get("stretcher_offsets");

    cerr<<"Calculated  calib loadedasdasd"<<endl;

    returnHisto = (TH1F*)(tmp->Clone("stretcher_offsets"));
    returnHisto->SetDirectory(dir);

    cerr<<"Calculated  calib loaded"<<endl;

    file->Close();
  }

  return returnHisto;

}

bool Unpacker2::calculateTimes(Event * old_event, Event * new_event){

  int localIndex;

  pArray = old_event->GetTDCHitsArray();
  if (pArray == 0) return false;
  iter = new TIter(pArray);

  for(int l = 0; l < REF_CHANNELS_NUMBER; l++) {
    refTimeEpoch[l] = -222222;
    refTimeCoarse[l] = -222222;
    refTimeFine[l] = -222222;
  }

  // fetch the reference times
  while( (pHit = (TDCHit*) iter->Next()) ) {
    if (pHit->GetChannel() % refChannelOffset == 0){

      refTimeEpoch[pHit->GetChannel() / refChannelOffset] = pHit->GetLeadEpoch(0);
      refTimeCoarse[pHit->GetChannel() / refChannelOffset] = pHit->GetLeadCoarse(0);
      refTimeFine[pHit->GetChannel() / refChannelOffset] = pHit->GetLeadFine(0);

      double leadTime = (double) ( (((unsigned)pHit->GetLeadEpoch(0)) << 11) * 5.0);
      leadTime += ( ( (pHit->GetLeadCoarse(0) * 5000.) - (pHit->GetLeadFine(0))) / 1000.);

      TDCHitExtended* new_hit = new_event->AddTDCHitExtended(pHit->GetChannel());
      new_hit->SetAbsoluteTimeLine(leadTime, 0);
      new_hit->SetRisingEdge(true, 0);
      new_hit->SetAbsoluteTimeLine(leadTime + 10, 1);
      new_hit->SetRisingEdge(false, 1);
      new_hit->SetTimeLineSize(2);
    }
  }
  // create time lines for normal channels
  iter->Begin();
  while( (pHit = (TDCHit*) iter->Next()) ){
    if ( (pHit->GetLeadsNum() > 0 && pHit->GetTrailsNum() > 0) && ((pHit->GetChannel() % refChannelOffset) != 0) ){
      TDCHitExtended* new_hit = new_event->AddTDCHitExtended(pHit->GetChannel());
      //localTrailIndex = 0;
      //lastTime = -1;
      localIndex = 0;

      int tdc_number = pHit->GetChannel() / refChannelOffset;

      for (int j = 0; j < pHit->GetLeadsNum(); j++) {

        double leadTime = (double) (
                (
                        ( (((unsigned)pHit->GetLeadEpoch(j)) << 11) * 5.0) -
                        ( (((unsigned)refTimeEpoch[tdc_number]) << 11) * 5.0 )
                )
        );
        leadTime += ((((pHit->GetLeadCoarse(j) - refTimeCoarse[tdc_number]) * 5000.) - (pHit->GetLeadFine(j) - refTimeFine[tdc_number])) / 1000.);
        if (localIndex > 0) {
          for(int l = 0; l <= localIndex; l++)
          {
            if (leadTime < new_hit->GetAbsoluteTimeLine(l) || l == localIndex) {
              new_hit->ShiftEverythingUpByOne(l - 1);
              new_hit->SetAbsoluteTimeLine(leadTime, l);
              new_hit->SetRisingEdge(true, l);
              localIndex++;
              new_hit->SetTimeLineSize(localIndex);
              break;
            }
          }
        }
        else {
          new_hit->SetAbsoluteTimeLine(leadTime, 0);
          new_hit->SetRisingEdge(true, 0);
          localIndex++;
          new_hit->SetTimeLineSize(localIndex);
        }
      }
      for (int k = 0; k < pHit->GetTrailsNum(); k++){

        double trailTime = (double) (
                (
                        ( (((unsigned)pHit->GetTrailEpoch(k)) << 11) * 5.0) -
                        ( (((unsigned)refTimeEpoch[tdc_number]) << 11) * 5.0 )
                )
        );

        trailTime -= calibHist->GetBinContent(pHit->GetChannel() + 1);

        trailTime += ( (((pHit->GetTrailCoarse(k) - refTimeCoarse[tdc_number]) * 5000.) - (pHit->GetTrailFine(k) - refTimeFine[tdc_number])) / 1000.);

        if (localIndex > 0) {
          for(int l = 0; l <= localIndex; l++){
            if (trailTime < new_hit->GetAbsoluteTimeLine(l) || l == localIndex ) {
              new_hit->ShiftEverythingUpByOne(l - 1);
              new_hit->SetAbsoluteTimeLine(trailTime, l);
              new_hit->SetRisingEdge(false, l);
              localIndex++;
              new_hit->SetTimeLineSize(localIndex);
              break;
            }
          }
        }
        else {
          new_hit->SetAbsoluteTimeLine(trailTime, 0);
          new_hit->SetRisingEdge(false, 0);
          localIndex++;
          new_hit->SetTimeLineSize(localIndex);
        }
      }
      new_hit->SetTimeLineSize(localIndex);
    }
  }

  return true;
}


bool Unpacker2::calculateHits(Event * event, EventIII * eventIII){

  double actualLead = -100000;
  bool firstLeadFound = false;
  TDCHitExtended* pHit = 0;

  pArray = event->GetTDCHitsArray();
  if (pArray == 0) return false;
  iter = new TIter(pArray);

  while( (pHit = (TDCHitExtended*) iter->Next()) ){
    TDCChannel* new_ch = eventIII->AddTDCChannel(pHit->GetChannel());

    // hit construction logic
    actualLead = -100000;
    firstLeadFound = false;

    for (int j = 0; j < pHit->GetTimeLineSize(); j++) {
      if (pHit->GetRisingEdge(j) == true && firstLeadFound == false) {
        actualLead = pHit->GetAbsoluteTimeLine(j);
        firstLeadFound = true;
      }
      else if (pHit->GetRisingEdge(j) == false && firstLeadFound == true) {
        new_ch->AddHit(actualLead, pHit->GetAbsoluteTimeLine(j));
        firstLeadFound = false;
      }
    }
  }

  delete iter;

  return true;
}


size_t Unpacker2::getDataSize() {
  if (invertBytes == false) {
    return (size_t) (((SubEventHdr*)subPHdr)->size - 16);
  }
  else {
    return (size_t) (ReverseHex(((SubEventHdr*)subPHdr)->size) - 16);
  }

  return -1;
}

std::string Unpacker2::getHubAddress() {
  string s = "0000";
  stringstream sstream;
  if (invertBytes == false) {
    sstream<<hex<<((SubEventHdr*)subPHdr)->hubAddress;
  }
  else {
    sstream<<hex<<ReverseHex((UInt_t)((SubEventHdr*)subPHdr)->hubAddress);
  }
  //cerr<<s<<" |"<<sstream<<"| |";
  s = s.replace(4 - sstream.str().length(), sstream.str().length(), sstream.str());
  //cerr<<s<<"|"<<endl;

  return s;
}

size_t Unpacker2::ReverseHex(size_t n) {
  size_t a, b, c, d, e;
  a = n & 0x000000ff;
  b = n & 0x0000ff00;
  c = n & 0x00ff0000;
  d = n & 0xff000000;

  a <<= 24;
  b <<= 8;
  c >>= 8;
  d >>=24 ;

  e = a|b|c|d;

  return e;
}