#ifndef FILTER_EFFECTIVE_TIME_H
#define FILTER_EFFECTIVE_TIME_H

#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterEffectiveTime : public Filter
{
public:
 FilterEffectiveTime( JPetStatistics& stats, JPetParams& params );
 ~FilterEffectiveTime();

  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterEffectiveTime_Index_int";

 private: //Histograms names
  const std::string kH1EffectiveTimeForHitNo2Before = "EffectiveTimeForHitNo2_Before";
  const std::string kH1EffectiveTimeForHitNo2After = "EffectiveTimeForHitNo2_After"; 
  const std::string kH1EffectiveTimeForHitNo3Before = "EffectiveTimeForHitNo3_Before";
  const std::string kH1EffectiveTimeForHitNo3After = "EffectiveTimeForHitNo3_After";
  const std::string kH1EffectiveTimeForHitNo4Before = "EffectiveTimeForHitNo4_Before";
  const std::string kH1EffectiveTimeForHitNo4After = "EffectiveTimeForHitNo4_After";
  const std::string kH1EffectiveTimeForAllHitsBefore = "EffectiveTimeForAllHits_Before";
  const std::string kH1EffectiveTimeForAllHitsAfter = "EffectiveTimeForAllHits_After"; 

};

#endif
