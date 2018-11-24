#include "FilterLambdaFor3rdHit.h"
#include "TMath.h"
#include "TVector3.h"
#include "FilterCorrectedTime.h"

FilterLambdaFor3rdHit::FilterLambdaFor3rdHit( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterLambdaFor3rdHit" );
}

FilterLambdaFor3rdHit::~FilterLambdaFor3rdHit()
{
}

bool FilterLambdaFor3rdHit::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;
 if ( !fillDoubleParameter( kFilterLambdaMeanParamKey, kFilterLambdaMean ) )
  return false;
 if ( !fillDoubleParameter( kFilterLambdaWidthParamKey, kFilterLambdaWidth ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout << "kFilterLambdaMean = " << kFilterLambdaMean << std::endl;
 std::cout << " kFilterLambdaWidth = " <<  kFilterLambdaWidth << std::endl;
 coutLine();

 add2DHists( kH2Lambda_31_vs_32_Before, kH2Lambda_31_vs_32_After, 300 * 4, -150, 150, "#lambda_{13} [cm]", "#lambda_{23} [cm]" );
 add1DHists( kH1Hit3PairedWith_Before, kH1Hit3PairedWith_After, 5, -0.5, 4.5, "Hit3 paired with hit ", "Counts" );

 return true;
}

bool FilterLambdaFor3rdHit::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 std::vector<AnalysisData*> pointers_data = { &data[ 0 ], &data[ 1 ], &data[ 2 ], &data[ 3 ] };

 std::sort( pointers_data.begin(), pointers_data.end(), FilterCorrectedTime::SortDataByCorrectedTime );

 TVector3 k1 = pointers_data[ 0 ]->getHitPosition();
 TVector3 k2 = pointers_data[ 1 ]->getHitPosition();
 TVector3 k3 = pointers_data[ 2 ]->getHitPosition();

 //std::cout << "FilterLambdaFor3rdHit::filterData: values from getCorrectedTime()" << std::endl; 
 //std::cout << pointers_data[ 0 ]->getCorrectedTime() << std::endl;
// std::cout << pointers_data[ 1 ]->getCorrectedTime() << std::endl;
// std::cout << pointers_data[ 2 ]->getCorrectedTime() << std::endl;

 TVector3 k13 = k1 - k3;
 TVector3 k23 = k2 - k3;

 double t1 = pointers_data[ 0 ]->getRawTime();
 double t2 = pointers_data[ 1 ]->getRawTime();
 double t3 = pointers_data[ 2 ]->getRawTime();

 double lambda_13 = k13.Mag() - kLightVeclocityInVacuum * ( t3 - t1 );
 double lambda_23 = k23.Mag() - kLightVeclocityInVacuum * ( t3 - t2 );

 //std::cout << "VALUES: lambda_13 = " << lambda_13 << " lambda_23 = " << lambda_23 << std::endl; 

 bool passed_13 = TMath::Abs( TMath::Abs( lambda_13 ) - kFilterLambdaMean ) < kFilterLambdaWidth;
 bool passed_23 = TMath::Abs( TMath::Abs( lambda_23 ) - kFilterLambdaMean ) < kFilterLambdaWidth;

 bool passed = false;
 int paired_with = 0;

 if ( passed_13 && !passed_23 )
 {
  passed = true;
  pointers_data[ 2 ]->setMotherGammaIndex( 0 );
  paired_with = 1;
 }
 else if ( !passed_13 && passed_23 )
 {
  passed = true;
  pointers_data[ 2 ]->setMotherGammaIndex( 1 );
  paired_with = 2;
 }
 else if ( passed_13 && passed_23 )
 {
  paired_with = 3;
 }

 //std::cout << "lambda_13 = " << lambda_13 << " lambda_23 = " << lambda_23 << std::endl;

 noticeFor2DHists( kH2Lambda_31_vs_32_Before, kH2Lambda_31_vs_32_After, passed, lambda_13, lambda_23 );
 noticeFor1DHists( kH1Hit3PairedWith_Before, kH1Hit3PairedWith_After, passed, paired_with );

 return !passed;
}
