#ifndef FILTER_COMPTON_THETA_ANGLE_H
#define FILTER_COMPTON_THETA_ANGLE_H

#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterComptonThetaAngle : public Filter
{
 public:
  FilterComptonThetaAngle( JPetStatistics& stats, JPetParams& params );
  ~FilterComptonThetaAngle();

  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterComptonThetaAngle_Index_int";
  const std::string kFilterThetaMinimumValueParamKey = "FilterComptonThetaAngle_ThetaMinimuValue_float";
  const std::string kFilterThetaMaximumValueParamKey = "FilterComptonThetaAngle_ThetaMaximumValue_float";

 private: //Parameters values
  double kFilterThetaMinimumValue; //[deg]
  double kFilterThetaMaximumValue; //[deg]

 private: //Histograms names
  const std::string kH1ComptonThetaAllBefore = "ComptonTheta_All_Before";
  const std::string kH1ComptonThetaAllAfter = "ComptonTheta_All_After";

  const std::string kH1ComptonTheta13Before = "ComptonTheta_13_Before";
  const std::string kH1ComptonTheta13After = "ComptonTheta_13_After";

  const std::string kH1ComptonTheta24Before = "ComptonTheta_24_Before";
  const std::string kH1ComptonTheta24After = "ComptonTheta_24_After";

  const std::string kH2ComptonTheta13vs24Before = "ComptonTheta_13_vs_24_Before";
  const std::string kH2ComptonTheta13vs24After = "ComptonTheta_13_vs_24_After";
};

#endif
