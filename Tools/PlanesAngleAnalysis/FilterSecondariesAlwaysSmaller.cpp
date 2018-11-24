#include "FilterSecondariesAlwaysSmaller.h"

FilterSecondariesAlwaysSmaller::FilterSecondariesAlwaysSmaller( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterSecondariesAlwaysSmaller" );
}

FilterSecondariesAlwaysSmaller::~FilterSecondariesAlwaysSmaller()
{
}

bool FilterSecondariesAlwaysSmaller::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 coutLine();

 add1DHists( kH1DeltaTOT13Before, kH1DeltaTOT13After, 1000, -50, 50, "#Delta TOT_{13} [ns]", "Counts" );
 add1DHists( kH1DeltaTOT14Before, kH1DeltaTOT14After, 1000, -50, 50, "#Delta TOT_{14} [ns]", "Counts" );
 add1DHists( kH1DeltaTOT23Before, kH1DeltaTOT23After, 1000, -50, 50, "#Delta TOT_{23} [ns]", "Counts" );
 add1DHists( kH1DeltaTOT24Before, kH1DeltaTOT24After, 1000, -50, 50, "#Delta TOT_{24} [ns]", "Counts" );
 add1DHists( kH1DeltaTOTAllBefore, kH1DeltaTOTAllAfter, 1000, -50, 50, "#Delta TOT [ns]", "Counts" );
 add2DHists( kH2DeltaTOT23vs13Before, kH2DeltaTOT23vs13After, 1000, -50, 50, "#Delta TOT_{13} [ns]", "#Delta TOT_{23} [ns]" );
 add2DHists( kH2DeltaTOT24vs14Before, kH2DeltaTOT24vs14After, 1000, -50, 50, "#Delta TOT_{14} [ns]", "#Delta TOT_{24} [ns]" );

 return true;
}

bool FilterSecondariesAlwaysSmaller::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 double tot1 = data[ 0 ].getTOT();
 double tot2 = data[ 1 ].getTOT();
 double tot3 = data[ 2 ].getTOT();
 double tot4 = data[ 3 ].getTOT();

 double tot13 = tot1 - tot3;
 double tot23 = tot2 - tot3;

 double tot14 = tot1 - tot4;
 double tot24 = tot2 - tot4;

 bool passed = ( ( tot13 > 0 ) || ( tot23 > 0 ) ) && ( ( tot14 > 0 ) || ( tot24 > 0 ) );

 noticeFor1DHists( kH1DeltaTOT13Before, kH1DeltaTOT13After, passed, tot13 );
 noticeFor1DHists( kH1DeltaTOT14Before, kH1DeltaTOT14After, passed, tot14 );
 noticeFor1DHists( kH1DeltaTOT23Before, kH1DeltaTOT23After, passed, tot23 );
 noticeFor1DHists( kH1DeltaTOT24Before, kH1DeltaTOT24After, passed, tot24 );

 noticeFor1DHists( kH1DeltaTOTAllBefore, kH1DeltaTOTAllAfter, passed, tot13 );
 noticeFor1DHists( kH1DeltaTOTAllBefore, kH1DeltaTOTAllAfter, passed, tot14 );
 noticeFor1DHists( kH1DeltaTOTAllBefore, kH1DeltaTOTAllAfter, passed, tot23 );
 noticeFor1DHists( kH1DeltaTOTAllBefore, kH1DeltaTOTAllAfter, passed, tot24 );

 noticeFor2DHists( kH2DeltaTOT23vs13Before, kH2DeltaTOT23vs13After, passed, tot13, tot23 );
 noticeFor2DHists( kH2DeltaTOT24vs14Before, kH2DeltaTOT24vs14After, passed, tot14, tot24 );
 
 return !passed;
}


