#ifndef FILTER_CORRECTED_TIME_H
#define FILTER_CORRECTED_TIME_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterCorrectedTime : public Filter
{
 public:
  FilterCorrectedTime( JPetStatistics& stats, JPetParams& params );
  ~FilterCorrectedTime();

  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

  static bool SortDataByCorrectedTime( const AnalysisData* da, const AnalysisData* db );

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterCorrectedTime_Index_int";
  const std::string kFilterCorrectedTimeSigmaParamKey = "FilterCorrectedTimeSigma_float";

 private: //Parameters values
  double kFilterCorrectedTimeSigma;

 private: //Histograms names

  const std::string kH1CorrectedTime_21_Before = "CorrectedTime_21_Before";
  const std::string kH1CorrectedTime_21_After = "CorrectedTime_21_After";
  const std::string kH1CorrectedTime_31_Before = "CorrectedTime_31_Before";
  const std::string kH1CorrectedTime_31_After = "CorrectedTime_31_After";
  const std::string kH1CorrectedTime_41_Before = "CorrectedTime_41_Before";
  const std::string kH1CorrectedTime_41_After = "CorrectedTime_41_After";
};

#endif
