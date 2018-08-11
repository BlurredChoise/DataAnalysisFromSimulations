#ifndef AnalysisClass_h
#define AnalysisClass_h

namespace ToolsForAnalysis
{
 class AnalysisClass
 {
  public:
   AnalysisClass();
   virtual ~AnalysisClass();
   virtual void analyzeEntry() = 0;
 };
};

#endif
