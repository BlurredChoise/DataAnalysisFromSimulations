#include "FilterCorrectedTimeDiff41.h"

FilterCorrectedTimeDiff41::FilterCorrectedTimeDiff41( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterCorrectedTimeDiff41" );
}

FilterCorrectedTimeDiff41::~FilterCorrectedTimeDiff41()
{
}

bool FilterCorrectedTimeDiff41::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;
 if ( !fillDoubleParameter( kFilterCorrectedTimeDiff41ParamKey, kFilterTimeDiff41 ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout << "kFilterTimeDiff41 = " << kFilterTimeDiff41 << std::endl;
 coutLine();

 add1DHists( kH1TimeDiff41_Before, kH1TimeDiff41_After, 800, -100, 100, "T_{corr} [ns]", "Counts" );

 return true;
}

bool FilterCorrectedTimeDiff41::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 double tdiff_41 = data[3].getCorrectedTime() - data[0].getCorrectedTime();

 bool passed = tdiff_41 > kFilterTimeDiff41;
 
 noticeFor1DHists( kH1TimeDiff41_Before, kH1TimeDiff41_After, passed, tdiff_41 );
 
 return !passed;
}
