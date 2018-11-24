#include "FilterEffectiveTime.h"

FilterEffectiveTime::FilterEffectiveTime( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterEffectiveTime" );
}

FilterEffectiveTime::~FilterEffectiveTime()
{
}

bool FilterEffectiveTime::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 coutLine();

 add1DHists( kH1EffectiveTimeForHitNo2Before, kH1EffectiveTimeForHitNo2After, 602, -1, 30 , "T_{eff} [ns]", "Counts" );
 add1DHists( kH1EffectiveTimeForHitNo3Before, kH1EffectiveTimeForHitNo3After, 602, -1, 30 , "T_{eff} [ns]", "Counts" );
 add1DHists( kH1EffectiveTimeForHitNo4Before, kH1EffectiveTimeForHitNo4After, 602, -1, 30 , "T_{eff} [ns]", "Counts" );
 add1DHists( kH1EffectiveTimeForAllHitsBefore, kH1EffectiveTimeForAllHitsAfter, 602, -1, 30 , "T_{eff} [ns]", "Counts" );
 return true;
}

bool FilterEffectiveTime::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 double t2 = data[1].getEffectiveTime();
 double t3 = data[2].getEffectiveTime();
 double t4 = data[3].getEffectiveTime();

 bool passed = ( t2 < t3 ) && ( t3 < t4 );

 noticeFor1DHists( kH1EffectiveTimeForHitNo2Before, kH1EffectiveTimeForHitNo2After, passed, t2 );
 noticeFor1DHists( kH1EffectiveTimeForHitNo3Before, kH1EffectiveTimeForHitNo3After, passed, t3 );
 noticeFor1DHists( kH1EffectiveTimeForHitNo4Before, kH1EffectiveTimeForHitNo4After, passed, t4 );

 noticeFor1DHists( kH1EffectiveTimeForAllHitsBefore, kH1EffectiveTimeForAllHitsAfter, passed, t2 );
 noticeFor1DHists( kH1EffectiveTimeForAllHitsBefore, kH1EffectiveTimeForAllHitsAfter, passed, t3 );
 noticeFor1DHists( kH1EffectiveTimeForAllHitsBefore, kH1EffectiveTimeForAllHitsAfter, passed, t4 );

 return !passed;
}


