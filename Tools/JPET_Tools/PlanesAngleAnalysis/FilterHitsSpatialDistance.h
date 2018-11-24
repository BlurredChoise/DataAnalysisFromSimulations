#ifndef FILTER_SPATIAL_DISTANCE_H
#define FILTER_SPATIAL_DISTANCE_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterHitsSpatialDistance : public Filter
{
 public:
  FilterHitsSpatialDistance( JPetStatistics& stats, JPetParams& params );
  ~FilterHitsSpatialDistance();

  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterHitsSpatialDistance_Index_int";
  const std::string kFilterSpatialDistanceParamKey = "FilterHitsSpatialDistance_SpatialDistance_float";
 private: //Parameters values
  double kFilterSpatialDistance; //[cm]
 private: //Histograms names
  const std::string kH1SpatialDistance12Before = "SpatialDistance12_Before";
  const std::string kH1SpatialDistance12After = "SpatialDistance12_After";
  const std::string kH1SpatialDistance13Before = "SpatialDistance13_Before";
  const std::string kH1SpatialDistance13After = "SpatialDistance13_After";
  const std::string kH1SpatialDistance14Before = "SpatialDistance14_Before";
  const std::string kH1SpatialDistance14After = "SpatialDistance14_After";
  const std::string kH1SpatialDistance23Before = "SpatialDistance23_Before";
  const std::string kH1SpatialDistance23After = "SpatialDistance23_After";
  const std::string kH1SpatialDistance24Before = "SpatialDistance24_Before";
  const std::string kH1SpatialDistance24After = "SpatialDistance24_After";
  const std::string kH1SpatialDistance34Before = "SpatialDistance34_Before";
  const std::string kH1SpatialDistance34After = "SpatialDistance34_After";
};

#endif

