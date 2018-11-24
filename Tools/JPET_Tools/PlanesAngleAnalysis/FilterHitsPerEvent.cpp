#include "FilterHitsPerEvent.h"

FilterHitsPerEvent::FilterHitsPerEvent( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterHitsPerEvent" );
}

FilterHitsPerEvent::~FilterHitsPerEvent()
{
}

bool FilterHitsPerEvent::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;
 if ( !fillUnsignedIntParameter( kFilterHitsNumberParamKey, kHitsPerEvent ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout<<"kFilterHitsNumber = "<<kHitsPerEvent<<std::endl;
 coutLine();

 add1DHists( kH1HitsPerEventBefore, kH1HitsPerEventAfter, 31, -0.5, 30.5 , "Number of hits per event", "Counts" );
 return true;
}

bool FilterHitsPerEvent::filterData( std::vector<AnalysisData>& data ) 
{
 bool passed = data.size() == kHitsPerEvent;
 noticeFor1DHists( kH1HitsPerEventBefore, kH1HitsPerEventAfter, passed, data.size() );
 return !passed;
}


