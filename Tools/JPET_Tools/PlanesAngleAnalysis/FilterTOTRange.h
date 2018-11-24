#ifndef FILTER_TOT_RANGE_H
#define FILTER_TOT_RANGE_H
#include "Filter.h"
#include <string>
#include "AnalysisData.h"
#include <vector>
#include <JPetParams/JPetParams.h>
#include <JPetStatistics/JPetStatistics.h>

class FilterTOTRange : public Filter
{
 public:
  struct HistTOTData
  {
   static HistTOTData getHTD( std::string hnb, std::string hna, double tot,  std::string hnb2, std::string hna2, int sciID );
   std::string kHistogramNameBefore;
   std::string kHistogramNameAfter;
   double fTOT;
   std::string kHistogramNameBefore2D;
   std::string kHistogramNameAfter2D;
   int fSciID;
  };

 public:
  FilterTOTRange( JPetStatistics& stats, JPetParams& params );
  ~FilterTOTRange();

  virtual bool initStatistics() override;
  virtual bool filterData( std::vector<AnalysisData>& data ) override;

 private: //Parameter keys
  const std::string kFilterIndexParamKey = "FilterTOTRange_Index_int";
  const std::string kFilterTOTMinimumValueParamKey = "FilterTOTRange_MinTOT_float";
  const std::string kFilterTOTMaximumValueParamKey = "FilterTOTRange_MaxTOT_float";
  const std::string kFilterCheckFirstNHitsParamKey = "FilterTOTRange_CheckFirstNHits_int";//Maksymlanie 4 można sprawdzić
  const std::string kFilterDataFromSimulationParamKey = "FilterTOTRange_DataFromSimulation_bool";//Jeżeli to jest ustawione to MinTOT i MaxTOt są traktowane jako wartości w keV

 private: //Parameters values
  double kFilterTOTMinimumValue;
  double kFilterTOTMaximumValue;
  unsigned int kFilterCheckFirstNHits;
  bool kDataFromSimulation = false;

  private: //Histograms names
  const std::string kH1TOTNo1Before = "TOTRangeNo1_Before";
  const std::string kH1TOTNo1After = "TOTRangeNo1_After";
  const std::string kH1TOTNo2Before = "TOTRangeNo2_Before";
  const std::string kH1TOTNo2After = "TOTRangeNo2_After";
  const std::string kH1TOTNo3Before = "TOTRangeNo3_Before";
  const std::string kH1TOTNo3After = "TOTRangeNo3_After";
  const std::string kH1TOTNo4Before = "TOTRangeNo4_Before";
  const std::string kH1TOTNo4After = "TOTRangeNo4_After";
  const std::string kH1TOTAllBefore = "TOTRangeAll_Before";
  const std::string kH1TOTAllAfter = "TOTRangeAll_After";

  const std::string kH2TOTNo1Before = "TOTRangeVsScintilatorIDNo1_Before";
  const std::string kH2TOTNo1After = "TOTRangeVsScintilatorIDNo1_After";
  const std::string kH2TOTNo2Before = "TOTRangeVsScintilatorIDNo2_Before";
  const std::string kH2TOTNo2After = "TOTRangeVsScintilatorIDNo2_After";
  const std::string kH2TOTNo3Before = "TOTRangeVsScintilatorIDNo3_Before";
  const std::string kH2TOTNo3After = "TOTRangeVsScintilatorIDNo3_After";
  const std::string kH2TOTNo4Before = "TOTRangeVsScintilatorIDNo4_Before";
  const std::string kH2TOTNo4After = "TOTRangeVsScintilatorIDNo4_After";
  const std::string kH2TOTAllBefore = "TOTRangeVsScintilatorIDAll_Before";
  const std::string kH2TOTAllAfter = "TOTRangeVsScintilatorIDAll_After";

  private: //Other variables

  std::vector< HistTOTData > fHistNameVsTOT;
  
};


#endif
