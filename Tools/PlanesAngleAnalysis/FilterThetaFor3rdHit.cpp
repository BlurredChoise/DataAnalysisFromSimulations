#include "FilterThetaFor3rdHit.h"
#include "TMath.h"
#include "TVector3.h"

FilterThetaFor3rdHit::FilterThetaFor3rdHit( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterThetaFor3rdHit" );
}

FilterThetaFor3rdHit::~FilterThetaFor3rdHit()
{
}

bool FilterThetaFor3rdHit::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;
 if ( !fillDoubleParameter( kFilterThetaMeanParamKey, kFilterThetaMean ) )
  return false;
 if ( !fillDoubleParameter( kFilterThetaWidthParamKey, kFilterThetaWidth ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout << "kFilterThetaMean = " << kFilterThetaMean << std::endl;
 std::cout << " kFilterThetaWidth = " <<  kFilterThetaWidth << std::endl;
 coutLine();

 add2DHists( kH2Theta_31_vs_32_Before, kH2Theta_31_vs_32_After, 724, -1, 180, "#theta_{32} [deg]", "#theta_{31} [deg]" );

 return true;
}

bool FilterThetaFor3rdHit::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 3 )
  return false;

 TVector3 k1 = data[ 0 ].getHitPosition();
 TVector3 k2 = data[ 1 ].getHitPosition();
 TVector3 k3 = data[ 2 ].getHitPosition();

 double theta_31 = k3.Angle( k1 ) * TMath::RadToDeg();
 double theta_32 = k3.Angle( k2 ) * TMath::RadToDeg();

 bool passed =  ( TMath::Abs( theta_31 - kFilterThetaMean ) < kFilterThetaWidth ) && ( TMath::Abs( theta_32 - kFilterThetaMean ) < kFilterThetaWidth );

 noticeFor2DHists( kH2Theta_31_vs_32_Before, kH2Theta_31_vs_32_After, passed, theta_32, theta_31 );
 
 return !passed;
}
