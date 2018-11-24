#include<iostream>
#include "FiltersManager.h"
#include "FilterComptonThetaAngle.h"
#include "FilterEffectiveTime.h"
#include "FilterHitsPerEvent.h"
#include "FilterMinimumHitsPerEvent.h"
#include "FilterParallerPrimeGammas.h"
#include "FilterReferenceTime.h"
#include "FilterSecondariesAlwaysSmaller.h"
#include "FilterTOTRange.h"
#include "FilterThetasSums.h"
#include "FilterHitsSpatialDistance.h"
#include "FilterCorrectedTime.h"
#include "FilterCorrectedTimeDiff41.h"
#include "FilterThetaFor3rdHit.h"
#include "FilterThetaFor4thHit.h"
#include "FilterLambdaFor3rdHit.h"
#include "FilterLambdaFor4thHit.h"

#include <algorithm>
#include <JPetOptionsTools/JPetOptionsTools.h>
using namespace jpet_options_tools;

FiltersManager::FiltersManager( JPetStatistics& stats, JPetParams& params )
{
 fStatistics = &stats;
 fParams = &params;
}

FiltersManager::~FiltersManager()
{
 for ( unsigned int i = 0; i < fFilters.size(); ++i )
  delete fFilters[i];
 fFilters.clear();
}

void FiltersManager::initFilters()
{
 scanOptions();

 for ( unsigned int i = 0; i < fFilters.size(); ++i )
  fFilters[i]->initStatistics();
 
 std::sort( fFilters.begin(), fFilters.end(), sortFilters );

 for ( unsigned int i = 0; i < fFilters.size(); ++i )
  std::cout << fFilters[i]->getName() << " " << fFilters[i]->getIndex() << std::endl;
}

bool FiltersManager::isFiltrationPassed( std::vector< AnalysisData >& data )
{
 for ( unsigned int i = 0; i < fFilters.size(); ++i )
  if ( fFilters[i]->filterData( data ) )
   return false;
 return true;
}

void FiltersManager::scanOptions()
{
 if ( isEnableFilter( kFilterComptonThetaAngleParamKey ) )
  addFilterToList( new FilterComptonThetaAngle( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterEffectiveTimeParamKey ) )
  addFilterToList( new FilterEffectiveTime( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterHitsPerEventParamKey ) )
  addFilterToList( new FilterHitsPerEvent( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterMinimumHitsPerEventParamKey ) )
  addFilterToList( new FilterMinimumHitsPerEvent( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterParallerPrimeGammasParamKey ) )
  addFilterToList( new FilterParallerPrimeGammas( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterReferenceTimeParamKey ) )
  addFilterToList( new FilterReferenceTime( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterSecondariesAlwaysSmallerParamKey ) )
  addFilterToList( new FilterSecondariesAlwaysSmaller( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterTOTRangeParamKey ) )
  addFilterToList( new FilterTOTRange( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterThetasSumsParamKey ) )
  addFilterToList( new FilterThetasSums( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterHitsSpatialDistanceParamKey ) )
  addFilterToList( new FilterHitsSpatialDistance( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterCorrectedTimeParamKey ) )
  addFilterToList( new FilterCorrectedTime( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterCorrectedTimeDiff41ParamKey ) )
  addFilterToList( new FilterCorrectedTimeDiff41( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterThetaFor3rdHitParamKey ) )
  addFilterToList( new FilterThetaFor3rdHit( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterThetaFor4thHitParamKey ) )
  addFilterToList( new FilterThetaFor4thHit( *fStatistics, *fParams ) );

 if ( isEnableFilter( kFilterLambdaFor3rdHitParamKey ) )
  addFilterToList( new FilterLambdaFor3rdHit( *fStatistics, *fParams ) );

  if ( isEnableFilter( kFilterLambdaFor4thHitParamKey ) )
  addFilterToList( new FilterLambdaFor4thHit( *fStatistics, *fParams ) );
}

bool FiltersManager::isEnableFilter( std::string filter_name )
{
 if ( isOptionSet( fParams->getOptions(), filter_name ) && getOptionAsBool( fParams->getOptions(), filter_name ) )
  return true;
 return false;
}

void FiltersManager::addFilterToList( Filter* filter )
{
 fFilters.push_back( filter );
}

bool FiltersManager::sortFilters( const Filter* filter_A, const Filter* filter_B )
{
 return filter_A->getIndex() < filter_B->getIndex();
}
