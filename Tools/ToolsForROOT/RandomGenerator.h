#ifndef RandomGenerator_h
#define RandomGenerator_h
#include "TRandom3.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This is simple class provide generator of random numbers. At this moment there is only support for normal distribution.
*/
namespace ToolsForROOT
{
 class RandomGenerator
 {
  public:
   RandomGenerator();
   ~RandomGenerator();

   void initGenerator( unsigned int seed = 0 );
   double getValueFromNormalDistribution( const double& mean, const double& sigma ) const;
   double getValueFromNormalDistributionInRange( const double& mean, const double& sigma ) const;
   void setRangeForNormalDistribution( const double& xmin, const double& xmax );
   double getValueFromUniformDistribution() const;
   void setSeed( unsigned int seed );

  private:
   double getValueNormalDistribution() const;
   double getValueUniformDistribution() const;

  private:
   TRandom3* ptrGenerator = nullptr;
   double fRangeNormalMin = 0;
   double fRangeNormalMax = 0;
 };
};

#endif
