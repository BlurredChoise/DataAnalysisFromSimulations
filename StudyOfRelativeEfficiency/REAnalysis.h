#ifndef REAnalysis_h
#define REAnalysis_h
#include "../Tools/ToolsForAnalysis/AnalysisClass.h"
#include "REDataCreator.h"
#include "REData.h"
#include "../Tools/ToolsForROOT/RandomGenerator.h"
#include <string>
#include <vector>
#include "TH1F.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class perform analysis of data from simulation
File: REAnalysis.h
**/
class REAnalysis : public ToolsForAnalysis::AnalysisClass
{
 public:
  REAnalysis();
  virtual ~REAnalysis();
  virtual void analyzeEntry();

  void setCreator( REDataCreator* creator );

  void setSigmaEnergyThreshold( double sigma );
  void setMeanEnergyThreshold( double mean );
  void useSmearingEnergyThreshold( bool use );
  void setNormalDistributionRange( double xmin, double xmax );

  void useHitsSeparationByTime( bool use );

  void setSeed( unsigned int seed = 0 );

  void displayStatus();

 private:
  double getSmearedEnergyThreshold();

 private:
  REDataCreator* fCreator;
  ToolsForROOT::RandomGenerator fGenerator;

  double fSigmaEnergyThreshold = 0.0;
  double fMeanEnergyThreshold = 1.0;
  bool kUseSmearingEnergyThreshold = false;
  bool kUseHitsSeparationByTime = false;

  double fRangeMin = 0;
  double fRangeMax = 0;
  bool fIsRangeON = false;
  unsigned int fSeed = 0;

 // Section: ANALYSIS
 private:
  void analyzeDataSet();
  void calcThetaAndUpdateHitograms();
  void updateHits( REData** hAs1, REData** hAs2, REData** hBs1 );
  void separateByTime( REData** hAs1, REData** hAs2, REData** hBs1 );
  void separateByTrackID( REData** hAs1, REData** hAs2, REData** hBs1 );

 private: 
  std::vector<REData> fDatas;
  std::vector<REData*> fHits;
  int fEventID = -1;

 // Section: HISTOGRAMS
 public:
  void saveHistograms( std::string output_file_name );

 private: //Histograms management
  void initHistograms();
  void deleteHistograms();

 private: //Histograms
  bool kHistogramsSaved;//In case when we save histogram to file, we do not need to delete histograms
  TH1F* fH1EnergyDeposition;
  TH1F* fH1TrueTheta;
  TH1F* fH1FakeTheta;
  TH1F* fH1TrueAndFakeTheta;

 // Section: CONDITIONS
 public:
  void setEnergyDepositionCondition( double energy_threshold );

 private: //Conditions
  bool conditionHitsNumber();
  bool conditionHitsScattersNumber();
  bool conditionHitsScintilators();
  bool conditionHitsEnergyDeposition();
  bool conditionHitsZPosition();

 private:
  const unsigned int kHistNumber = 3;
  double fEnergyThreshold = 0.0;
  const double kZMinValue = -23.0;
  const double kZMaxValue = 23.0;

 private: //counters
  std::vector<unsigned int> fCounters;
 
};

#endif
