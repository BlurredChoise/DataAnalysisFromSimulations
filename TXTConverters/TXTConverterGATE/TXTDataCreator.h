#ifndef TXTDataCreator_h
#define TXTDataCreator_h
#include "../../Tools/ToolsForAnalysis/AnalysisDataCreatorClass.h"
#include "../../Tools/ToolsForAnalysis/AnalysisData.h"
#include "TXTData.h"
#include "../../Tools/ToolsForGATE/GlobalActorReader/GlobalActorReader.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class read raw data from simulation and convert them to format useful for analysis
File: TXTDataCreator.h
**/
class TXTDataCreator : public ToolsForAnalysis::AnalysisDataCreatorClass
{
 public:
  TXTDataCreator();
  virtual ~TXTDataCreator();
  virtual void extractDataFromEntry();
  virtual ToolsForAnalysis::AnalysisData* getData();

  void setReader( ToolsForGATE::GlobalActorReader* reader );
  
 private:
  TXTData fData;
  ToolsForGATE::GlobalActorReader* fReader = nullptr;
  int fCurrentEventID = -1;
  int fCurrentTrackID = 0;
  unsigned int fCurrentScattersPerTrackIndex = 0;
};

#endif
