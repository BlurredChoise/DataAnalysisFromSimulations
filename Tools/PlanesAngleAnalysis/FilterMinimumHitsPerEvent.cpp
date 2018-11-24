#include<iostream>
#include "FilterMinimumHitsPerEvent.h"


FilterMinimumHitsPerEvent::FilterMinimumHitsPerEvent( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterMinimumHitsPerEvent" );
}

FilterMinimumHitsPerEvent::~FilterMinimumHitsPerEvent()
{
}

bool FilterMinimumHitsPerEvent::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;
 if ( !fillUnsignedIntParameter( kFilterMinimumHitsNumberParamKey, kMinimumHitsPerEvent ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout << "kMinimumHitsPerEvent = " << kMinimumHitsPerEvent << std::endl;
 coutLine();

 add1DHists( kH1MinimumHitsPerEventBefore, kH1MinimumHitsPerEventAfter, 31, -1, 30 , "Number of hits per event", "Counts" );
 return true;
}

bool FilterMinimumHitsPerEvent::filterData( std::vector<AnalysisData>& data ) 
{
 bool passed = data.size() >= kMinimumHitsPerEvent;
 noticeFor1DHists( kH1MinimumHitsPerEventBefore, kH1MinimumHitsPerEventAfter, passed, data.size() );
 return !passed;
}


