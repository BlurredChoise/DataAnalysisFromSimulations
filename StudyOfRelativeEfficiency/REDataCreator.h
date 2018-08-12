#ifndef REDataCreator_h
#define REDataCreator_h
#include "../Tools/ToolsForAnalysis/AnalysisDataCreatorClass.h"
#include "../Tools/ToolsForAnalysis/AnalysisData.h"
#include "REData.h"
#include "../Tools/ToolsForROOT/RandomGenerator.h"
#include "../Tools/ToolsForGATE/GlobalActorReader/GlobalActorReader.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class read raw data from simulation and convert them to format useful for analysis
File: REDataCreator.h
**/
class REDataCreator : public ToolsForAnalysis::AnalysisDataCreatorClass
{
 public:
  REDataCreator();
  virtual ~REDataCreator();
  virtual void extractDataFromEntry();
  virtual ToolsForAnalysis::AnalysisData* getData();

  void setReader( ToolsForGATE::GlobalActorReader* reader );

  void setSigmaZ( double sigma );
  void setSigmaTime( double sigma );

  void useSmearingZ( bool use );
  void useSmearingTime( bool use );
  void useSmearingEnergyDeposition( bool use );

  void setNormalDistributionRange( double xmin, double xmax );

  void setSeed( unsigned int seed );

  void displayStatus();
  
 private:
  double getSmearedZ( double z );
  double getSmearedEnergyDeposition( double energy );
  double getSmearedTime( double time );

  double calcSigmaEnergy( double energy );
  

 private:
  REData fData;
  ToolsForROOT::RandomGenerator fGenerator;
  ToolsForGATE::GlobalActorReader* fReader = nullptr;
  bool kUseSmearingZ = false;
  bool kUseSmearingTime = false;
  bool kUseSmearingEnergyDeposition = false;

  double fSigmaZ = 0.0;
  double fSigmaTime = 0.0;

  int fCurrentEventID = -1;
  int fCurrentTrackID = 0;
  unsigned int fCurrentScattersPerTrackIndex = 0;

  double fRangeMin = 0.0;
  double fRangeMax = 0.0;
  bool fIsRangeON = false;

  unsigned int fSeed = 0;

  const double kLightVelocityInVaccum = 29.979246; //[cm/ns]
};

#endif
