#ifndef FILTER_CORRECTED_TIME_DIFF41_H
#define FILTER_CORRECTED_TIME_DIFF41_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterCorrectedTimeDiff41 : public Filter
{
 public:
  FilterCorrectedTimeDiff41( JPetStatistics& stats, JPetParams& params );
  ~FilterCorrectedTimeDiff41();

  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterCorrectedTimeDiff41_Index_int";
  const std::string kFilterCorrectedTimeDiff41ParamKey = "FilterCorrectedTimeDiff41_TimeDiff41_float";

 private: //Parameters values
  double kFilterTimeDiff41; //[ns]

 private: //Histograms names
  const std::string kH1TimeDiff41_Before = "TimeDiff41_Before";
  const std::string kH1TimeDiff41_After = "TimeDiff41_After";
};

#endif
