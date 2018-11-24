#ifndef FILTER_LAMBDA_FOR_3RD_HIT_H
#define FILTER_LAMBDA_FOR_3RD_HIT_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterLambdaFor3rdHit : public Filter
{
 public:
  FilterLambdaFor3rdHit( JPetStatistics& stats, JPetParams& params );
  ~FilterLambdaFor3rdHit();

  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterLambdaFor3rdHit_Index_int";
  const std::string kFilterLambdaMeanParamKey = "FilterLambdaFor3rdHit_Mean_float";
  const std::string kFilterLambdaWidthParamKey = "FilterLambdaFor3rdHit_Width_float";

 private: //Parameters values
  double kFilterLambdaMean; //[deg]
  double kFilterLambdaWidth; //[deg]

 private: //Histograms names
  const std::string kH2Lambda_31_vs_32_Before = "Lambda_31_vs_32_Before";
  const std::string kH2Lambda_31_vs_32_After = "Lambda_31_vs_32_After";

  const std::string kH1Hit3PairedWith_Before = "Hit3PairedWith_Before";
  const std::string kH1Hit3PairedWith_After = "Hit3PairedWith_After";

 private: //Other
  const double kLightVeclocityInVacuum = 29.979246; //[cm/ns]
};

#endif
