#ifndef EfficiencyCounter_h
#define EfficiencyCounter_h
#include "../../Tools/ToolsForAnalysis/AnalysisClass.h"
#include "../DPDataCreator.h"
#include "../DPData.h"
#include <string>
#include <vector>
#include "TVector3.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class perform analysis of data from simulation and calc efficency
File: EfficiencyCounter.h
**/
class EfficiencyCounter : public ToolsForAnalysis::AnalysisClass
{
 public:
  EfficiencyCounter();
  virtual ~EfficiencyCounter();
  virtual void analyzeEntry();

  void setCreator( DPDataCreator* creator );

  void setOutputFileName( std::string output_file_name );
  void setSourceModelName( std::string source_model_name );
  void setGeometryNumber( unsigned int geometry_number );
  void setNumberOfGeneratedEvents( unsigned int number_of_generated_events );
  void setNumberOdGammasGeneratedPerEvent( unsigned int number_of_generated_gammas_per_events );
  void setEnergyThreshold( double energy_threshold );
  void setPromptEnergyThreshold( double energy_threshold );
  void setPromptEnergy( double energy );
  void saveResultsToFile();
  void saveHistograms( TFile* file );
  void setPromptVisible( bool prompts_here );
  
  
 private:
  void analyzeEvent();
  void initHistograms(); 

 private:
  std::string fOutputFileName = "";
  DPDataCreator* fCreator = nullptr;
  std::vector<DPData> fDatas;
  std::string fSourceModelName = "";
  unsigned int fNumberOfGammasGeneratedPerEvent = 0;
  unsigned int fGeometryNumber = 0;
  unsigned int fNumberOfGeneratedEvents = 0; //number of events generated by simulation
  double fEnergyThreshold = 0;
  double fPromptEnergyThreshold = 0;
  double fPromptEnergy = 0;
  bool fPromptInData = false;
  unsigned int fNumberOfDetectedEvents = 0;
  const TVector3 zero_vector = TVector3(0,0,0);
  int fEventID = -1;

 private: //Control counters
 unsigned int fCounterTotal = 0;
 unsigned int fCounterSize = 0;
 unsigned int fCounterFoundTracks = 0;
 unsigned int fCounterScintilators = 0;
 unsigned int fCounterAE = 0;
 std::vector<unsigned int> fCounterTracks;

 private: //Histograms - control histograms
 TH2F* h2XYHitPosition = nullptr;
 TH2F* h2XZHitPosition = nullptr;
 TH2F* h2YZHitPosition = nullptr;

 TH2F* h2XYHitPositionAccepted = nullptr;
 TH2F* h2XZHitPositionAccepted = nullptr;
 TH2F* h2YZHitPositionAccepted = nullptr;

 TH1F* h1NumberOfScattersPerTrack = nullptr; //Doesnt matter which track - statistci for all tracks
 TH1F* h1NumberOfScatteringPerTracksSet = nullptr;//Each one must scatter minimum N-times
 TH1F* h1NumberOfScattersPerTrackAccepted = nullptr;
 TH1F* h1EnergyDepositionAcceptedBeforeCuts = nullptr;
 TH1F* h1EnergyDepositionAcceptedAfterCuts = nullptr;

 TH1F* h1GammaEnergyAll = nullptr;
 TH1F* h1GammaEnergyAccepted = nullptr;

};

#endif