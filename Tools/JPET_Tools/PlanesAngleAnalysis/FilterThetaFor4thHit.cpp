#include "FilterThetaFor4thHit.h"
#include "TMath.h"
#include "TVector3.h"

FilterThetaFor4thHit::FilterThetaFor4thHit( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterThetaFor4thHit" );
}

FilterThetaFor4thHit::~FilterThetaFor4thHit()
{
}

bool FilterThetaFor4thHit::initStatistics()
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

 add2DHists( kH2Theta_41_vs_42_Before, kH2Theta_41_vs_42_After, 724, -1, 180, "#theta_{42} [deg]", "#theta_{41} [deg]" );

 return true;
}

bool FilterThetaFor4thHit::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 TVector3 k1 = data[ 0 ].getHitPosition();
 TVector3 k2 = data[ 1 ].getHitPosition();
 TVector3 k4 = data[ 3 ].getHitPosition();

 double theta_41 = k4.Angle( k1 ) * TMath::RadToDeg();
 double theta_42 = k4.Angle( k2 ) * TMath::RadToDeg();

 bool passed =  ( TMath::Abs( theta_41 - kFilterThetaMean ) < kFilterThetaWidth ) && ( TMath::Abs( theta_42 - kFilterThetaMean ) < kFilterThetaWidth );

 noticeFor2DHists( kH2Theta_41_vs_42_Before, kH2Theta_41_vs_42_After, passed, theta_42, theta_41 );
 
 return !passed;
}
