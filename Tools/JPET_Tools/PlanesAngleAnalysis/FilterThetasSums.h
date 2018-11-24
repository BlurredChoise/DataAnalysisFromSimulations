#ifndef FILTER_THETAS_SUMS_H
#define FILTER_THETAS_SUMS_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterThetasSums: public Filter
{
 public:
  FilterThetasSums( JPetStatistics& stats, JPetParams& params );
  ~FilterThetasSums();

  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

  static bool sortThetas( const double* theta_A, const double* theta_B );

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterThetasSums_Index_int";
  const std::string kFilterThetasSumMeanParamKey = "FilterThetasSums_ThetasSumMean_float";
  const std::string kFilterThetasSumWidthParamKey = "FilterThetasSums_ThetasSumWidth_float";
 private: //Parameters values
  double kFilterThetasSumMean; // [deg]
  double kFilterThetasSumWidth; // [deg]
 private: //Histograms names
  const std::string kH2ThetasSumsBefore = "ThetasSums_Before";
  const std::string kH2ThetasSumsAfter = "ThetasSums_After";
  const std::string kH2ThetasSumsIncludedTimeCorrectionIndexBefore = "ThetasSums_TCorrIndex_Before";
  const std::string kH2ThetasSumsIncludedTimeCorrectionIndexAfter = "ThetasSums_TCorrIndex_After";



};

#endif
