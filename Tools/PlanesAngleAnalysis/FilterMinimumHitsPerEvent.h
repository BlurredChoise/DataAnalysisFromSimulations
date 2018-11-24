#ifndef FILTER_MINIMUM_HITS_PER_EVENT
#define FILTER_MINIMUM_HITS_PER_EVENT

#include "Filter.h"
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>
/**
@FilterDescriptionStart
Accepts only events with hits number equal or greater then required
@FilterDescriptionEnd
**/
class FilterMinimumHitsPerEvent : public Filter
{
 public:
  FilterMinimumHitsPerEvent( JPetStatistics& stats, JPetParams& params );
  virtual ~FilterMinimumHitsPerEvent();
  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterMinimumHitsNumberParamKey = "FilterMinimumHitsPerEvent_HitsNumber_int";
  const std::string kFilterIndexParamKey = "FilterMinimumHitsPerEvent_Index_int";

 private: //Parameters values
  unsigned int kMinimumHitsPerEvent;

 private: //Histograms names
  const std::string kH1MinimumHitsPerEventBefore = "MinimumHitsPerEvent_Before";
  const std::string kH1MinimumHitsPerEventAfter = "MinimumHitsPerEvent_After";
};

#endif
