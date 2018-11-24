#include "FilterLambdaFor4thHit.h"
#include "TMath.h"
#include "TVector3.h"
#include "FilterCorrectedTime.h"

FilterLambdaFor4thHit::FilterLambdaFor4thHit( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterLambdaFor4thHit" );
}

FilterLambdaFor4thHit::~FilterLambdaFor4thHit()
{
}

bool FilterLambdaFor4thHit::initStatistics()
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

 add2DHists( kH2Lambda_41_vs_42_Before, kH2Lambda_41_vs_42_After, 300 * 4, -150, 150, "#lambda_{14} [cm]", "#lambda_{24} [cm]" );
 add1DHists( kH1Hit4PairedWith_Before, kH1Hit4PairedWith_After, 5, -0.5, 4.5, "Hit4 paired with hit ", "Counts" );

 return true;
}

bool FilterLambdaFor4thHit::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 std::vector<AnalysisData*> pointers_data = { &data[ 0 ], &data[ 1 ], &data[ 2 ], &data[ 3 ] };

 std::sort( pointers_data.begin(), pointers_data.end(), FilterCorrectedTime::SortDataByCorrectedTime );

 TVector3 k1 = pointers_data[ 0 ]->getHitPosition();
 TVector3 k2 = pointers_data[ 1 ]->getHitPosition();
 TVector3 k4 = pointers_data[ 3 ]->getHitPosition();

 TVector3 k14 = k1 - k4;
 TVector3 k24 = k2 - k4;

 double t1 = pointers_data[ 0 ]->getRawTime();
 double t2 = pointers_data[ 1 ]->getRawTime();
 double t4 = pointers_data[ 3 ]->getRawTime();

 double lambda_14 = k14.Mag() - kLightVeclocityInVacuum * ( t4 - t1 );
 double lambda_24 = k24.Mag() - kLightVeclocityInVacuum * ( t4 - t2 );

// std::cout << "VALUES: lambda_14 = " << lambda_14 << " lambda_24 = " << lambda_24 << std::endl;

 bool passed_14 = TMath::Abs( TMath::Abs( lambda_14 ) - kFilterLambdaMean ) < kFilterLambdaWidth;
 bool passed_24 = TMath::Abs( TMath::Abs( lambda_24 ) - kFilterLambdaMean ) < kFilterLambdaWidth;

 bool passed = false;
 int paired_with = 0;

 if ( passed_14 && !passed_24 )
 {
  passed = true;
  pointers_data[ 3 ]->setMotherGammaIndex( 0 );
  paired_with = 1;
 }
 else if ( !passed_14 && passed_24 )
 {
  passed = true;
  pointers_data[ 3 ]->setMotherGammaIndex( 1 );
  paired_with = 2;
 }
 else if ( passed_14 && passed_24 )
 {
  paired_with = 3;
 }

 if( pointers_data[ 3 ]->getMotherGammaIndex() == pointers_data[ 2 ]->getMotherGammaIndex() )
  passed = false;

 noticeFor2DHists( kH2Lambda_41_vs_42_Before, kH2Lambda_41_vs_42_After, passed, lambda_14, lambda_24 );
 noticeFor1DHists( kH1Hit4PairedWith_Before, kH1Hit4PairedWith_After, passed, paired_with );

 return !passed;
}
