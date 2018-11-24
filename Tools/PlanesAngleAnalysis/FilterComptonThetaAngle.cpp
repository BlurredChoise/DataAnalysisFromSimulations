#include "FilterComptonThetaAngle.h"
#include "TMath.h"
#include "FilterCorrectedTime.h"

FilterComptonThetaAngle::FilterComptonThetaAngle( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterComptonThetaAngle" );
}

FilterComptonThetaAngle::~FilterComptonThetaAngle()
{
}

bool FilterComptonThetaAngle::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;
 if ( !fillDoubleParameter( kFilterThetaMinimumValueParamKey, kFilterThetaMinimumValue ) )
  return false;
 if ( !fillDoubleParameter( kFilterThetaMaximumValueParamKey, kFilterThetaMaximumValue ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout << "kFilterThetaMinimumValue = " << kFilterThetaMinimumValue << std::endl;
 std::cout << "kFilterThetaMaximumValue = " << kFilterThetaMaximumValue << std::endl;
 coutLine();

 add1DHists( kH1ComptonThetaAllBefore, kH1ComptonThetaAllAfter, 721, -1, 180, "#theta [deg]", "Counts" );

 add1DHists( kH1ComptonTheta13Before, kH1ComptonTheta13After, 721, -1, 180, "#theta_{13} [deg]", "Counts" );

 add1DHists( kH1ComptonTheta24Before, kH1ComptonTheta24After, 721, -1, 180, "#theta_{24} [deg]", "Counts" );

 add2DHists( kH2ComptonTheta13vs24Before, kH2ComptonTheta13vs24After, 721, -1, 180, "#theta_{13} [deg]", "#theta_{24} [deg]");

 return true;
}

bool FilterComptonThetaAngle::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 //std::cout<< "FilterComptonThetaAngle::filterData" <<std::endl;

 std::vector<AnalysisData*> pointers_data = { &data[ 0 ], &data[ 1 ], &data[ 2 ], &data[ 3 ] };

 std::sort( pointers_data.begin(), pointers_data.end(), FilterCorrectedTime::SortDataByCorrectedTime );

 //std::cout<< " pointers_data[ 2 ]->getMotherGammaIndex() = " << pointers_data[ 2 ]->getMotherGammaIndex() << std::endl;
 //std::cout<< " pointers_data[ 3 ]->getMotherGammaIndex() = " << pointers_data[ 3 ]->getMotherGammaIndex() << std::endl;
 
 TVector3 k1 = pointers_data[ pointers_data[ 2 ]->getMotherGammaIndex() ]->getHitPosition(); 
 TVector3 k2 = pointers_data[ pointers_data[ 3 ]->getMotherGammaIndex() ]->getHitPosition();
 TVector3 k3 = pointers_data[ 2 ]->getHitPosition(); 
 TVector3 k4 = pointers_data[ 3 ]->getHitPosition(); 

 TVector3 k31 = k3 - k1;
 TVector3 k42 = k4 - k2;

 double theta_13 = k1.Angle( k31 ) * TMath::RadToDeg();
 double theta_24 = k2.Angle( k42 ) * TMath::RadToDeg();

 bool passed = ( theta_13 > kFilterThetaMinimumValue ) && ( theta_13 < kFilterThetaMaximumValue ) && ( theta_24 > kFilterThetaMinimumValue ) && ( theta_24 < kFilterThetaMaximumValue );

 //std::cout << "Filling histograms for theta " << std::endl;

 noticeFor1DHists( kH1ComptonThetaAllBefore, kH1ComptonThetaAllAfter, passed, theta_13 );
 noticeFor1DHists( kH1ComptonThetaAllBefore, kH1ComptonThetaAllAfter, passed, theta_24 );

 noticeFor1DHists( kH1ComptonTheta13Before, kH1ComptonTheta13After, passed, theta_13 );
 noticeFor1DHists( kH1ComptonTheta24Before, kH1ComptonTheta24After, passed, theta_24 );

 noticeFor2DHists( kH2ComptonTheta13vs24Before, kH2ComptonTheta13vs24After, passed, theta_13, theta_24 );
 
 return !passed;
}


