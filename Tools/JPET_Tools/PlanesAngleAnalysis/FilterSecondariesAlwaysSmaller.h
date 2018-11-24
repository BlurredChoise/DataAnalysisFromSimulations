#ifndef FILTER_SECONDARIES_ALWAYS_SMALLER
#define FILTER_SECONDARIES_ALWAYS_SMALLER
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterSecondariesAlwaysSmaller : public Filter
{
 public:
  FilterSecondariesAlwaysSmaller( JPetStatistics& stats, JPetParams& params );
  ~FilterSecondariesAlwaysSmaller();
  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterSecondariesAlwaysSmaller_Index_int";

 private: //Histograms names
  const std::string kH1DeltaTOT13Before = "DeltaTOT13_Before";
  const std::string kH1DeltaTOT13After = "DeltaTOT13_After";
  const std::string kH1DeltaTOT14Before = "DeltaTOT14_Before";
  const std::string kH1DeltaTOT14After = "DeltaTOT14_After";
  const std::string kH1DeltaTOT23Before = "DeltaTOT23_Before";
  const std::string kH1DeltaTOT23After = "DeltaTOT23_After";
  const std::string kH1DeltaTOT24Before = "DeltaTOT24_Before";
  const std::string kH1DeltaTOT24After = "DeltaTOT24_After";  
  const std::string kH2DeltaTOT23vs13Before = "DeltaTOT23vs13_Before";
  const std::string kH2DeltaTOT23vs13After = "DeltaTOT23vs13_After";
  const std::string kH2DeltaTOT24vs14Before = "DeltaTOT24vs14_Before";
  const std::string kH2DeltaTOT24vs14After = "DeltaTOT24vs14_After";
  const std::string kH1DeltaTOTAllBefore = "DeltaTOTAll_Before";
  const std::string kH1DeltaTOTAllAfter = "DeltaTOTAll_After";
};

#endif
