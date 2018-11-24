#include "FilterThetasSums.h"
#include "TMath.h"
#include "TVector3.h"
#include "FilterCorrectedTime.h"

FilterThetasSums::FilterThetasSums( JPetStatistics& stats, JPetParams& params )  : Filter( stats, params )
{
 setName( "FilterThetasSums" );
}

FilterThetasSums::~FilterThetasSums()
{
}

bool FilterThetasSums::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;
 if ( !fillDoubleParameter( kFilterThetasSumMeanParamKey, kFilterThetasSumMean ) )
  return false;
 if ( !fillDoubleParameter( kFilterThetasSumWidthParamKey, kFilterThetasSumWidth ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout << "kFilterThetasSumMean = " << kFilterThetasSumMean << std::endl;
 std::cout << "kFilterThetasSumWidth = " << kFilterThetasSumWidth << std::endl;
 coutLine();

 add2DHists( kH2ThetasSumsBefore, kH2ThetasSumsAfter, 742*2, -1, 370, "#theta_{1'2'} + #theta_{2'3'} [deg]", "#theta_{1'2'} - #theta_{2'3'} [deg]");
 add2DHists( kH2ThetasSumsIncludedTimeCorrectionIndexBefore, kH2ThetasSumsIncludedTimeCorrectionIndexAfter, 742*2, -1, 370, "#theta_{1'2'} + #theta_{2'3'} [deg]", "#theta_{1'2'} - #theta_{2'3'} [deg]");
 return true;
}

bool FilterThetasSums::sortThetas( const double* theta_A, const double* theta_B )
{
 return *theta_A < *theta_B;
}

bool FilterThetasSums::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 std::vector<AnalysisData*> pointers_data = { &data[ 0 ], &data[ 1 ], &data[ 2 ], &data[ 3 ] };
 std::sort( pointers_data.begin(), pointers_data.end(), FilterCorrectedTime::SortDataByCorrectedTime );

 TVector3 k1 = pointers_data[ 0 ]->getHitPosition();
 TVector3 k2 = pointers_data[ 1 ]->getHitPosition();
 TVector3 k3 = pointers_data[ 2 ]->getHitPosition();

 double theta_12 = k1.Angle( k2 ) * TMath::RadToDeg();
 double theta_13 = k1.Angle( k3 ) * TMath::RadToDeg();
 double theta_23 = k2.Angle( k3 ) * TMath::RadToDeg();

 double* ptr_theta_12 = &theta_12;
 double* ptr_theta_13 = &theta_13;
 double* ptr_theta_23 = &theta_23;

 std::vector<double*> ptrs_thetas = { ptr_theta_12, ptr_theta_13, ptr_theta_23 };
 std::sort( ptrs_thetas.begin(), ptrs_thetas.end(), FilterThetasSums::sortThetas );

 double theta_sum = TMath::Abs( ( *ptrs_thetas[ 0 ] ) + ( *ptrs_thetas[ 1 ] ) );
 double theta_diff = TMath::Abs( ( *ptrs_thetas[ 0 ] ) - ( *ptrs_thetas[ 1 ] ) );

 bool passed = TMath::Abs( theta_sum - kFilterThetasSumMean ) < kFilterThetasSumWidth;

 noticeFor2DHists( kH2ThetasSumsBefore, kH2ThetasSumsAfter, passed, theta_sum, theta_diff);

 passed = passed && ( ( ( ptrs_thetas[ 0 ] == ptr_theta_12 ) && ( ptrs_thetas[ 1 ] == ptr_theta_23 ) ) || ( ( ptrs_thetas[ 1 ] == ptr_theta_12 ) && ( ptrs_thetas[ 0 ] == ptr_theta_23 ) ) );

 noticeFor2DHists( kH2ThetasSumsIncludedTimeCorrectionIndexBefore, kH2ThetasSumsIncludedTimeCorrectionIndexAfter, passed, theta_sum, theta_diff);

 return !passed;
}

