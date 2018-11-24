#ifndef FILTER_LAMBDA_FOR_4th_HIT_H
#define FILTER_LAMBDA_FOR_4th_HIT_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterLambdaFor4thHit : public Filter
{
 public:
  FilterLambdaFor4thHit( JPetStatistics& stats, JPetParams& params );
  ~FilterLambdaFor4thHit();

  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterLambdaFor4thHit_Index_int";
  const std::string kFilterLambdaMeanParamKey = "FilterLambdaFor4thHit_Mean_float";
  const std::string kFilterLambdaWidthParamKey = "FilterLambdaFor4thHit_Width_float";

 private: //Parameters values
  double kFilterLambdaMean; //[deg]
  double kFilterLambdaWidth; //[deg]

 private: //Histograms names
  const std::string kH2Lambda_41_vs_42_Before = "Lambda_41_vs_42_Before";
  const std::string kH2Lambda_41_vs_42_After = "Lambda_41_vs_42_After";

  const std::string kH1Hit4PairedWith_Before = "Hit4PairedWith_Before";
  const std::string kH1Hit4PairedWith_After = "Hit4PairedWith_After";

 private: //Other
  const double kLightVeclocityInVacuum = 29.979246; //[cm/ns]
};

#endif
