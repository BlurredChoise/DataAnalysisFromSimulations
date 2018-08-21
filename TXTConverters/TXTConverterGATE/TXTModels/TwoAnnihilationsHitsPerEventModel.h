#ifndef TwoAnnihilationsHitsPerEventModel_h
#define TwoAnnihilationsHitsPerEventModel_h
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
About: This class extract only oair of gammas from annihilation
File: TwoAnnihilationsHitsPerEventModel.h
**/
class TwoAnnihilationsHitsPerEventModel : public TXTModel
{
 public:
  TwoAnnihilationsHitsPerEventModel();
  virtual ~TwoAnnihilationsHitsPerEventModel();
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
  TH2F* h2HitPositionXY = nullptr;
  TH2F* h2HitPositionXZ = nullptr;
  TH2F* h2HitPositionYZ = nullptr;
  bool fHistogramSavedToFile = false;

 // Section: CONDITIONS
 private:
  bool conditionHitsNumber();
  bool conditionHitsScintilators();
  bool conditionHitsKind();
 private:
  const unsigned int kRequiredHitsNumber = 2;
 
};

#endif
