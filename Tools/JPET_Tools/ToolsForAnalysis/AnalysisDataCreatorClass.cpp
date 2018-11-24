#include "AnalysisDataCreatorClass.h"

namespace ToolsForAnalysis
{
 AnalysisDataCreatorClass::AnalysisDataCreatorClass() {}
 AnalysisDataCreatorClass::~AnalysisDataCreatorClass() {}

 void AnalysisDataCreatorClass::stopJob() { fStopJob = true; }
 bool AnalysisDataCreatorClass::isJobFinished() { return fStopJob; }

};
