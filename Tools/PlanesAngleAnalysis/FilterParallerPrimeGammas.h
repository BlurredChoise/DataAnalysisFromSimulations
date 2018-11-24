#ifndef PARALLER_PRIME_GAMMAS_H
#define PARALLER_PRIME_GAMMAS_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterParallerPrimeGammas : public Filter
{
 public:
  FilterParallerPrimeGammas( JPetStatistics& stats, JPetParams& params );
  ~FilterParallerPrimeGammas();
  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterParallerPrimeGammas_Index_int";
  const std::string kFilterAngleDeltaThetaParamKey = "FilterParallerPrimeGammas_DeltaTheta_float";

 private: //Parameters values
  double kFilterAngleDeltaTheta; //[deg]

 private: //Histograms names
  const std::string kH1AngleBetweenHitsBefore = "AngleBetweenHits_Before";
  const std::string kH1AngleBetweenHitsAfter = "AngleBetweenHits_After";
};

#endif
