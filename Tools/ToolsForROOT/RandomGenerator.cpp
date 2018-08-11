#include "RandomGenerator.h"
namespace ToolsForROOT
{

 RandomGenerator::RandomGenerator() {}

 RandomGenerator::~RandomGenerator()
 {
  if ( ptrGenerator != nullptr )
   delete ptrGenerator;
 }

 void RandomGenerator::initGenerator( unsigned int seed )
 {
  ptrGenerator = new TRandom3( seed );
 }

 double RandomGenerator::getValueFromNormalDistribution( const double& mean, const double& sigma ) const
 {
  return ptrGenerator->Gaus( mean, sigma );
 }

 double RandomGenerator::getValueFromNormalDistributionInRange( const double& mean, const double& sigma ) const
 {
  bool value_in_range = false;
  double value = 0;
  double min_value = fRangeNormalMin * sigma;
  double max_value = fRangeNormalMax * sigma;
  while ( !value_in_range )
  {
   value = ptrGenerator->Gaus( mean, sigma );
   if ( min_value <= value && value <= max_value )
    value_in_range = true;
  }
  return value;
 }

 void RandomGenerator::setRangeForNormalDistribution( const double& xmin, const double& xmax )
 {
  fRangeNormalMin = xmin;
  fRangeNormalMax = xmax;
 }

 double RandomGenerator::getValueFromUniformDistribution() const { return getValueUniformDistribution() ; }

 double RandomGenerator::getValueNormalDistribution() const { return ptrGenerator->Gaus( 0.0, 1.0 ); }

 double RandomGenerator::getValueUniformDistribution() const { return ptrGenerator->Uniform( 0.0, 1.0 ); }

 void RandomGenerator::setSeed( unsigned int seed ) { ptrGenerator->SetSeed( seed ); }
};
