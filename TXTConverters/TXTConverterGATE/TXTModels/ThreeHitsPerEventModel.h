#ifndef ThreeHitsPerEventModel_h
#define ThreeHitsPerEventModel_h
#include "TXTModel.h"
#include "../TXTDataCreator.h"
#include "../TXTData.h"
#include <string>
#include <vector>
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include <fstream>

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class perform analysis of data from simulation
File: ThreeHitsPerEventModel.h
**/
class ThreeHitsPerEventModel : public TXTModel
{
 public:
  ThreeHitsPerEventModel();
  virtual ~ThreeHitsPerEventModel();
  virtual void analyzeEntry();

  void setCreator( TXTDataCreator* creator );

  virtual void setOutputFileName( std::string output_file_name );
  virtual void setEventsNumberToSave( unsigned int events_to_generate );


 private:
  TXTDataCreator* fCreator;
  std::string fTXTFileName;
  std::string fControlROOTFileName;
  int fEventID = -1;
  unsigned int fEventsNumberToSave = 0;
  unsigned int fCurrentEventsNumberSaved = 0;

 // Section: ANALYSIS 
 private:
  void analyzeEvent();

 private: 
  std::vector<TXTData> fDatas;
  TXTData hit1, hit2, hit3;
  std::fstream fTXTFile;
  bool fIsOpenedTXTFile = false;

 // Section: HISTOGRAMS
 public:
  virtual void saveHistograms();

 private: //Histograms management
  void initHistograms();
  void deleteHistograms();

 private: //Histograms
  TH1F* h1EnergyDeposition;
  TH2F* h2HitPositionXY;
  TH2F* h2HitPositionXZ;
  TH2F* h2HitPositionYZ;
  TH2F* h2ScattersPerTrack_1_vs_2;
  TH2F* h2ScattersPerTrack_1_vs_3;
  TH2F* h2ScattersPerTrack_2_vs_3;
  TH1F* h1ScatteringKind;
  bool fHistogramSavedToFile = false;

 // Section: CONDITIONS
 private:
  bool conditionHitsNumber();
  bool conditionHitsScintilators();
  bool conditionEnergyConditionForFirstScatter();
 private:
  const unsigned int kRequiredHitsNumber = 3;
  const double kWindowSize = 40000.0;

 private: //Counters
  unsigned int fTotalEventsNumber = 0;
  unsigned int fFirstCondition = 0;
  unsigned int fSecondCondition = 0;
  unsigned int fThirdCondition = 0;
 
};

#endif
