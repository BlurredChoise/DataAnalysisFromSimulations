#include "FilterHitsSpatialDistance.h"
#include "TVector3.h"

FilterHitsSpatialDistance::FilterHitsSpatialDistance( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterHitsSpatialDistance" );
}

FilterHitsSpatialDistance::~FilterHitsSpatialDistance()
{
}

bool FilterHitsSpatialDistance::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;

 if ( !fillDoubleParameter( kFilterSpatialDistanceParamKey, kFilterSpatialDistance ) )
  return false;

 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout << "kFilterSpatialDistance = "<< kFilterSpatialDistance << std::endl;
 coutLine();

 add1DHists( kH1SpatialDistance12Before, kH1SpatialDistance12After, 2001, -1, 200 , "|d_{12}| [cm]", "Counts" );
 add1DHists( kH1SpatialDistance13Before, kH1SpatialDistance13After, 2001, -1, 200 , "|d_{13}| [cm]", "Counts" );
 add1DHists( kH1SpatialDistance14Before, kH1SpatialDistance14After, 2001, -1, 200 , "|d_{14}| [cm]", "Counts" );
 add1DHists( kH1SpatialDistance23Before, kH1SpatialDistance23After, 2001, -1, 200 , "|d_{23}| [cm]", "Counts" );
 add1DHists( kH1SpatialDistance24Before, kH1SpatialDistance24After, 2001, -1, 200 , "|d_{24}| [cm]", "Counts" );
 add1DHists( kH1SpatialDistance34Before, kH1SpatialDistance34After, 2001, -1, 200 , "|d_{34}| [cm]", "Counts" );

 return true;
}

bool FilterHitsSpatialDistance::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < 4 )
  return false;

 TVector3 k1 = data[ 0 ].getHitPosition();
 TVector3 k2 = data[ 1 ].getHitPosition();
 TVector3 k3 = data[ 2 ].getHitPosition();
 TVector3 k4 = data[ 3 ].getHitPosition();

 TVector3 k12 = k1 - k2;
 TVector3 k13 = k1 - k3;
 TVector3 k14 = k1 - k4;
 TVector3 k23 = k2 - k3;
 TVector3 k24 = k2 - k4;
 TVector3 k34 = k3 - k4;

 double d12 = k12.Mag();
 double d13 = k13.Mag();
 double d14 = k14.Mag();
 double d23 = k23.Mag();
 double d24 = k24.Mag();
 double d34 = k34.Mag();

 bool passed = ( d12 > kFilterSpatialDistance ) && ( d13 > kFilterSpatialDistance ) && ( d14 > kFilterSpatialDistance );
 passed = passed && ( d23 > kFilterSpatialDistance ) && ( d24 > kFilterSpatialDistance ) && ( d34 > kFilterSpatialDistance );

 noticeFor1DHists( kH1SpatialDistance12Before, kH1SpatialDistance12After, passed, d12 );
 noticeFor1DHists( kH1SpatialDistance13Before, kH1SpatialDistance13After, passed, d13 );
 noticeFor1DHists( kH1SpatialDistance14Before, kH1SpatialDistance14After, passed, d14 );
 noticeFor1DHists( kH1SpatialDistance23Before, kH1SpatialDistance23After, passed, d23 );
 noticeFor1DHists( kH1SpatialDistance24Before, kH1SpatialDistance24After, passed, d24 );
 noticeFor1DHists( kH1SpatialDistance34Before, kH1SpatialDistance34After, passed, d34 );

 return !passed;
}

