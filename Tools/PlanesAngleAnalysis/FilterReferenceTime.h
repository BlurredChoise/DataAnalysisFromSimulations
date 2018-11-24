#ifndef FILETR_REFERENCE_TIME_H
#define FILETR_REFERENCE_TIME_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

/**
@FilterDescriptionStart
Take second, third and fourth hit and comper theirs reference times. Accept only when t2 < t3 < t4
@FilterDescriptionEnd
**/
class FilterReferenceTime : public Filter
{
 public:
  FilterReferenceTime( JPetStatistics& stats, JPetParams& params );
  virtual ~FilterReferenceTime();

  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterReferenceTime_Index_int";

 private: //Histograms names
  const std::string kH1ReferenceTimeForHitNo2Before = "ReferenceTimeForHitNo2_Before";
  const std::string kH1ReferenceTimeForHitNo2After = "ReferenceTimeForHitNo2_After"; 
  const std::string kH1ReferenceTimeForHitNo3Before = "ReferenceTimeForHitNo3_Before";
  const std::string kH1ReferenceTimeForHitNo3After = "ReferenceTimeForHitNo3_After";
  const std::string kH1ReferenceTimeForHitNo4Before = "ReferenceTimeForHitNo4_Before";
  const std::string kH1ReferenceTimeForHitNo4After = "ReferenceTimeForHitNo4_After";
  const std::string kH1ReferenceTimeForAllHitsBefore = "ReferenceTimeForAllHits_Before";
  const std::string kH1ReferenceTimeForAllHitsAfter = "ReferenceTimeForAllHits_After";   
};

#endif
