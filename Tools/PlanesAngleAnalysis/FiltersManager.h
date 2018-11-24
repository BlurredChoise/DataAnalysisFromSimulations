#ifndef FILTERS_MANAGER_H
#define FILTERS_MANAGER_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FiltersManager
{
 public:
  FiltersManager( JPetStatistics& stats, JPetParams& params );
  ~FiltersManager();
  void initFilters();
  bool isFiltrationPassed( std::vector< AnalysisData >& data );
  static bool sortFilters( const Filter* filter_A, const Filter* filter_B );
 private:
  void scanOptions();
  bool isEnableFilter( std::string filter_name );
  void addFilterToList( Filter* filter );
 private:
  std::vector< Filter* > fFilters;
 private: //Command for calling filters
  const std::string kFilterComptonThetaAngleParamKey = "FiltersManager_FilterComptonThetaAngle_Enable_bool";
  const std::string kFilterEffectiveTimeParamKey = "FiltersManager_FilterEffectiveTime_Enable_bool";
  const std::string kFilterHitsPerEventParamKey = "FiltersManager_FilterHitsPerEvent_Enable_bool";
  const std::string kFilterMinimumHitsPerEventParamKey = "FiltersManager_FilterMinimumHitsPerEvent_Enable_bool";
  const std::string kFilterParallerPrimeGammasParamKey = "FiltersManager_FilterParallerPrimeGammas_Enable_bool";
  const std::string kFilterReferenceTimeParamKey = "FiltersManager_FilterReferenceTime_Enable_bool";
  const std::string kFilterSecondariesAlwaysSmallerParamKey = "FiltersManager_FilterSecondariesAlwaysSmaller_Enable_bool";
  const std::string kFilterTOTRangeParamKey = "FiltersManager_FilterTOTRange_Enable_bool";
  const std::string kFilterThetasSumsParamKey = "FiltersManager_FilterThetasSums_bool";
  const std::string kFilterHitsSpatialDistanceParamKey = "FiltersManager_FilterHitsSpatialDistance_bool";
  const std::string kFilterCorrectedTimeParamKey = "FiltersManager_FilterCorrectedTime_bool";
  const std::string kFilterCorrectedTimeDiff41ParamKey = "FiltersManager_FilterCorrectedTimeDiff41_bool";
  const std::string kFilterThetaFor3rdHitParamKey = "FiltersManager_FilterThetaFor3rdHit_bool";
  const std::string kFilterThetaFor4thHitParamKey = "FiltersManager_FilterThetaFor4thHit_bool";
  const std::string kFilterLambdaFor3rdHitParamKey = "FilterManager_FilterLambdaFor3rdHit_bool";
  const std::string kFilterLambdaFor4thHitParamKey = "FilterManager_FilterLambdaFor4thHit_bool";

  JPetStatistics* fStatistics;
  JPetParams* fParams;
 
};

#endif
