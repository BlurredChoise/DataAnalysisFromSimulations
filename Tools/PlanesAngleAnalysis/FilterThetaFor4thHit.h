#ifndef FILTER_THETA_DIFF_4th_HIT_H
#define FILTER_THETA_DIFF_4th_HIT_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterThetaFor4thHit : public Filter
{
 public:
  FilterThetaFor4thHit( JPetStatistics& stats, JPetParams& params );
  ~FilterThetaFor4thHit();
  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterThetaDiffFor4thHit_Index_int";
  const std::string kFilterThetaMeanParamKey = "FilterThetaFor4thHit_Mean_float";
  const std::string kFilterThetaWidthParamKey = "FilterThetaFor4thHit_Width_float";

 private: //Parameters values
  double kFilterThetaMean; //[deg]
  double kFilterThetaWidth; //[deg]

 private: //Histograms names
  const std::string kH2Theta_41_vs_42_Before = "Theta_41_vs_43_Before";
  const std::string kH2Theta_41_vs_42_After = "Theta_41_vs_42_After";
};

#endif
