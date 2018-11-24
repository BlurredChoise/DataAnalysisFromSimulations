#include "FilterParallerPrimeGammas.h"
#include "TVector3.h"
#include "TMath.h"

FilterParallerPrimeGammas::FilterParallerPrimeGammas( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterParallerPrimeGammas" );
}

FilterParallerPrimeGammas::~FilterParallerPrimeGammas()
{
}

bool FilterParallerPrimeGammas::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;
 if ( !fillDoubleParameter( kFilterAngleDeltaThetaParamKey, kFilterAngleDeltaTheta ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout << "kFilterAngleDeltaTheta = " << kFilterAngleDeltaTheta << std::endl;
 coutLine();

 add1DHists( kH1AngleBetweenHitsBefore, kH1AngleBetweenHitsAfter, 724, -1, 180, "#theta_{12} [deg]", "Counts" );

 return true;
}

bool FilterParallerPrimeGammas::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 2 )
  return false;

 TVector3 k1 = data[ 0 ].getHitPosition();
 TVector3 k2 = data[ 1 ].getHitPosition();

 double theta12 = k1.Angle( k2 ) * TMath::RadToDeg();

 bool passed =  ( 180.0 - theta12 ) < kFilterAngleDeltaTheta;

 noticeFor1DHists( kH1AngleBetweenHitsBefore, kH1AngleBetweenHitsAfter, passed, theta12 );
 
 return !passed;
}


