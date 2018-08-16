#ifndef TXTModel_h
#define TXTModel_h
#include "../../../Tools/ToolsForAnalysis/AnalysisClass.h"
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
File: TXTModel.h
**/
class TXTModel : public ToolsForAnalysis::AnalysisClass
{
 public:
  TXTModel();
  virtual ~TXTModel();
  virtual void analyzeEntry();

  virtual void setCreator( TXTDataCreator* creator );

  virtual void setOutputFileName( std::string output_file_name );
  virtual void setEventsNumberToSave( unsigned int events_to_generate );
  virtual void saveHistograms();
};

#endif
