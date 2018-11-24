#include "FilterCorrectedTime.h"
#include "TMath.h"


FilterCorrectedTime::FilterCorrectedTime( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterCorrectedTime" );
}

FilterCorrectedTime::~FilterCorrectedTime()
{
}

bool FilterCorrectedTime::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;
 if ( !fillDoubleParameter( kFilterCorrectedTimeSigmaParamKey, kFilterCorrectedTimeSigma ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout << "kFilterCorrectedTimeSigma = " << kFilterCorrectedTimeSigma << std::endl;
 coutLine();

 add1DHists( kH1CorrectedTime_21_Before, kH1CorrectedTime_21_After, 1001, 0, 100, "T_{21}^{corr} [ns]", "Counts" );
 add1DHists( kH1CorrectedTime_31_Before, kH1CorrectedTime_31_After, 1001, 0, 100, "T_{31}^{corr} [ns]", "Counts" );
 add1DHists( kH1CorrectedTime_41_Before, kH1CorrectedTime_41_After, 1001, 0, 100, "T_{41}^{corr} [ns]", "Counts" );

 return true;
}

bool FilterCorrectedTime::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 std::vector<AnalysisData*> pointers_data = { &data[ 0 ], &data[ 1 ], &data[ 2 ], &data[ 3 ] };

 std::sort( pointers_data.begin(), pointers_data.end(), FilterCorrectedTime::SortDataByCorrectedTime );

 for( unsigned int index = 0; index < 4; ++index )
  pointers_data[ index ]->setCorrectedTimeIndex( index );

 double Tcorr1 = pointers_data[ 0 ]->getCorrectedTime();
 double Tcorr2 = pointers_data[ 1 ]->getCorrectedTime();
 double Tcorr3 = pointers_data[ 2 ]->getCorrectedTime();
 double Tcorr4 = pointers_data[ 3 ]->getCorrectedTime();

 bool passed = ( TMath::Abs( Tcorr1 - Tcorr2 ) <= kFilterCorrectedTimeSigma ) && ( TMath::Abs( Tcorr2 - Tcorr3 ) <= kFilterCorrectedTimeSigma );
 passed = passed && ( TMath::Abs( Tcorr3 - Tcorr4 ) <= kFilterCorrectedTimeSigma );
 
 noticeFor1DHists( kH1CorrectedTime_21_Before, kH1CorrectedTime_21_After, passed, Tcorr2 - Tcorr1 );
 noticeFor1DHists( kH1CorrectedTime_31_Before, kH1CorrectedTime_31_After, passed, Tcorr3 - Tcorr1 );
 noticeFor1DHists( kH1CorrectedTime_41_Before, kH1CorrectedTime_41_After, passed, Tcorr4 - Tcorr1 );
 
 return !passed;
}

bool FilterCorrectedTime::SortDataByCorrectedTime( const AnalysisData* da, const AnalysisData* db )
{
 return da->getCorrectedTime() < db->getCorrectedTime();
}
