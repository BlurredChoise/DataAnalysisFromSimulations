#include "FilterReferenceTime.h"

FilterReferenceTime::FilterReferenceTime( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterReferenceTime" );
}

FilterReferenceTime::~FilterReferenceTime()
{
}

bool FilterReferenceTime::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 coutLine();

 add1DHists( kH1ReferenceTimeForHitNo2Before, kH1ReferenceTimeForHitNo2After, 602, -1, 30 , "T_{ref} [ns]", "Counts" );
 add1DHists( kH1ReferenceTimeForHitNo3Before, kH1ReferenceTimeForHitNo3After, 602, -1, 30 , "T_{ref} [ns]", "Counts" );
 add1DHists( kH1ReferenceTimeForHitNo4Before, kH1ReferenceTimeForHitNo4After, 602, -1, 30 , "T_{ref} [ns]", "Counts" );
 add1DHists( kH1ReferenceTimeForAllHitsBefore, kH1ReferenceTimeForAllHitsAfter, 602, -1, 30 , "T_{ref} [ns]", "Counts" );
 return true;
}

bool FilterReferenceTime::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 double t2 = data[ 1 ].getReferenceTime();
 double t3 = data[ 2 ].getReferenceTime();
 double t4 = data[ 3 ].getReferenceTime();

 bool passed = ( t2 < t3 ) && ( t3 < t4 );

 noticeFor1DHists( kH1ReferenceTimeForHitNo2Before, kH1ReferenceTimeForHitNo2After, passed, t2 );
 noticeFor1DHists( kH1ReferenceTimeForHitNo3Before, kH1ReferenceTimeForHitNo3After, passed, t3 );
 noticeFor1DHists( kH1ReferenceTimeForHitNo4Before, kH1ReferenceTimeForHitNo4After, passed, t4 );

 noticeFor1DHists( kH1ReferenceTimeForAllHitsBefore, kH1ReferenceTimeForAllHitsAfter, passed, t2 );
 noticeFor1DHists( kH1ReferenceTimeForAllHitsBefore, kH1ReferenceTimeForAllHitsAfter, passed, t3 );
 noticeFor1DHists( kH1ReferenceTimeForAllHitsBefore, kH1ReferenceTimeForAllHitsAfter, passed, t4 );

 return !passed;
}


