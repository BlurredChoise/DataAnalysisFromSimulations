#ifndef AnalysisDataCreatorClass_h
#define AnalysisDataCreatorClass_h
#include "AnalysisData.h"

namespace ToolsForAnalysis
{
 class AnalysisDataCreatorClass
 {
  public:
   AnalysisDataCreatorClass();
   virtual ~AnalysisDataCreatorClass();
   virtual void extractDataFromEntry() = 0;
   virtual AnalysisData* getData() = 0;
 };
};

#endif
