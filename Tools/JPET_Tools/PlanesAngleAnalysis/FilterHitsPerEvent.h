#ifndef FILTER_HITS_PER_EVENT
#define FILTER_HITS_PER_EVENT

#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

/**
@FilterDescriptionStart
Accepts only events with hits number equal requred.
@FilterDescriptionEnd
**/
class FilterHitsPerEvent : public Filter
{
 public:
  FilterHitsPerEvent( JPetStatistics& stats, JPetParams& params );
  virtual ~FilterHitsPerEvent();
  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterHitsNumberParamKey = "FilterHitsPerEvent_HitsNumber_int";
  const std::string kFilterIndexParamKey = "FilterHitsPerEvent_Index_int";

 private: //Parameters values
  unsigned int kHitsPerEvent;

 private: //Histograms names
  const std::string kH1HitsPerEventBefore = "HitsPerEvent_Before";
  const std::string kH1HitsPerEventAfter = "HitsPerEvent_After";
};

#endif
