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
  TH3F* h3HitPositionXYZ;
  TH2F* h2ScattersPerTrack;
  bool fHistogramSavedToFile = false;

 // Section: CONDITIONS
 private:
  bool conditionHitsNumber();
  bool conditionHitsScintilators();
 private:
  const unsigned int kRequiredHitsNumber = 3;
 
};

#endif
