#ifndef TwoAnnihilationsHitsPerEventTimeSmearedModel_h
#define TwoAnnihilationsHitsPerEventTimeSmearedModel_h
#include "TXTModel.h"
#include "../TXTDataCreator.h"
#include "../TXTData.h"
#include <string>
#include <vector>
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include <fstream>
#include "../../../Tools/ToolsForROOT/RandomGenerator.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class extract only pair of gammas from annihilation and smear time
File: TwoAnnihilationsHitsPerEventModel.h
**/
class TwoAnnihilationsHitsPerEventTimeSmearedModel : public TXTModel
{
 public:
  TwoAnnihilationsHitsPerEventTimeSmearedModel();
  virtual ~TwoAnnihilationsHitsPerEventTimeSmearedModel();
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
  double getSmearedTime( const double& time ) const;
  double ps( const double& time_ns ) const;

 private: 
  std::vector<TXTData> fDatas;
  TXTData fHitTrack1, fHitTrack2;
  std::fstream fTXTFile;
  bool fIsOpenedTXTFile = false;

 // Section: HISTOGRAMS
 public:
  virtual void saveHistograms();

 private: //Histograms management
  void initHistograms();
  void deleteHistograms();
  void fillHistograms( TXTData& data );

 private: //Histograms
  TH1F* h1EnergyDeposition = nullptr;
  TH1F* h1TimeDifference = nullptr;
  TH1F* h1Energy = nullptr;
  TH2F* h2HitPositionXY = nullptr;
  TH2F* h2HitPositionXZ = nullptr;
  TH2F* h2HitPositionYZ = nullptr;
  TH1F* h1ScattersNumber = nullptr;

  TH1F* h1Times = nullptr;

  bool fHistogramSavedToFile = false;

 // Section: CONDITIONS
 private:
  bool conditionHitsNumber();
  bool conditionHitsScintilators();
  bool conditionHitsKind();

 private:
  const unsigned int kRequiredHitsNumber = 2;

 private: //Counters
  unsigned int fTotalEventsNumber = 0;
  unsigned int fFirstFilter = 0;
  unsigned int fSecondFilter = 0;
  unsigned int fThirdFilter = 0;

  // Generators
  ToolsForROOT::RandomGenerator fRandGen;
  const double kTimeSigma = 0.4;//ns
  

 
 
};

#endif
