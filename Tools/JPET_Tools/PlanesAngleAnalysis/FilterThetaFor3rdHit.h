#ifndef FILTER_THETA_DIFF_3RD_HIT_H
#define FILTER_THETA_DIFF_3RD_HIT_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterThetaFor3rdHit : public Filter
{
 public:
  FilterThetaFor3rdHit( JPetStatistics& stats, JPetParams& params );
  ~FilterThetaFor3rdHit();
  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterThetaFor3rdHit_Index_int";
  const std::string kFilterThetaMeanParamKey = "FilterThetaFor3rdHit_Mean_float";
  const std::string kFilterThetaWidthParamKey = "FilterThetaFor3rdHit_Width_float";

 private: //Parameters values
  double kFilterThetaMean; //[deg]
  double kFilterThetaWidth; //[deg]

 private: //Histograms names
  const std::string kH2Theta_31_vs_32_Before = "Theta_31_vs_32_Before";
  const std::string kH2Theta_31_vs_32_After = "Theta_31_vs_32_After";
};

#endif
