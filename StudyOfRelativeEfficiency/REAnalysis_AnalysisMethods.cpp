#include "REAnalysis.h"
#include "TMath.h"
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class perform analysis of data from simulation
File: REAnalysis_AnalysisMethods.cpp - here is the proper analysis of data
**/

void REAnalysis::analyzeDataSet()
{
 ++fCounters[0];

 if ( !conditionHitsNumber() ) { return; }
 ++fCounters[1];
 if ( !conditionHitsScattersNumber() ) { return; }
 ++fCounters[2];
 if ( !conditionHitsScintilators() ) { return; }
 ++fCounters[3];
 if ( !conditionHitsEnergyDeposition() ) { return; }
 ++fCounters[4];
 if ( !conditionHitsZPosition() ) { return; }
 ++fCounters[5];

 /**
 At this moment we have exactly 3 hits ( 2 hits from gamma A and one from gamma B) - each one scattered in different scintillator, deposited energy above energy threshold 
 and has hit position in required range.
 From this point we can focus on time and theta angle analysis and then calculate required values for histograms
 **/
 calcThetaAndUpdateHitograms();
}

void REAnalysis::calcThetaAndUpdateHitograms()
{
 REData* hAs1 = nullptr;
 REData* hAs2 = nullptr;
 REData* hBs1 = nullptr; //h - hit, s - scatter
 updateHits( &hAs1, &hAs2, &hBs1 );
 if ( hAs1 == nullptr || hAs2 == nullptr || hBs1 == nullptr )
  return;
 ++fCounters[6];
 TVector3 kA1 = hAs1->getHitPosition();
 TVector3 kA2 = hAs2->getHitPosition();
 TVector3 kB1 = hBs1->getHitPosition();

 TVector3 kA21 = kA2 - kA1; //True scattered gamma momentum direction
 TVector3 kA2B1 = kA2 - kB1;//Fake scattered gamma momentum direction

 double theta_true = kA21.Angle( kA1 ) * TMath::RadToDeg();
 double theta_fake = kA2B1.Angle( kB1 ) * TMath::RadToDeg();

 double energy_deposited_during_first_true_scatter = hAs1->getEnergyDeposition();
 
 fH1EnergyDeposition->Fill( energy_deposited_during_first_true_scatter );
 fH1TrueTheta->Fill( theta_true );
 fH1FakeTheta->Fill( theta_fake );
 fH1TrueAndFakeTheta->Fill( theta_true );
 fH1TrueAndFakeTheta->Fill( theta_fake );
}

void REAnalysis::updateHits( REData** hAs1, REData** hAs2, REData** hBs1 )
{
 if ( kUseHitsSeparationByTime )
  separateByTime( hAs1, hAs2, hBs1 );
 else
  separateByTrackID( hAs1, hAs2, hBs1 );
}

void REAnalysis::separateByTime( REData** hAs1, REData** hAs2, REData** hBs1 )
{
 //Todo
}

void REAnalysis::separateByTrackID( REData** hAs1, REData** hAs2, REData** hBs1 )
{
 REData* hit1 = fHits[ 0 ];
 REData* hit2 = fHits[ 1 ];
 
 //We only need one condition - this is result of what does the method REAnalysis::conditionHitsScattersNumber()
 if ( hit1->getTrackID() ==  hit2->getTrackID() )
 {
  *hAs1 = fHits[ 0 ];
  *hAs2 = fHits[ 1 ];
  *hBs1 = fHits[ 2 ];
 }
 else
 {
  *hAs1 = fHits[ 1 ];
  *hAs2 = fHits[ 2 ];
  *hBs1 = fHits[ 0 ];
 }
}

bool REAnalysis::conditionHitsNumber()
{
 return fDatas.size() >= kHistNumber;
}

bool REAnalysis::conditionHitsScattersNumber()
{
 REData* hit_1_first_scatter = nullptr;
 REData* hit_1_second_scatter = nullptr;
 REData* hit_2_first_scatter = nullptr;
 REData* hit_2_second_scatter = nullptr;

 int size = fDatas.size();
  
 for ( unsigned int n = 0; n < size; ++n )
 {
  REData* hit = &fDatas[ n ];

  if ( hit->getTrackID() == 1 && hit->getScatteringIndex() == 1 )
   hit_1_first_scatter = hit;
  else if ( hit->getTrackID() == 1 && hit->getScatteringIndex() == 2 )
   hit_1_second_scatter = hit;
  else if ( hit->getTrackID() == 2 && hit->getScatteringIndex() == 1 )
   hit_2_first_scatter = hit;
  else if ( hit->getTrackID() == 2 && hit->getScatteringIndex() == 2 )
   hit_2_second_scatter = hit;
 }

 if ( hit_1_first_scatter != nullptr && hit_1_second_scatter  != nullptr && hit_2_first_scatter != nullptr && hit_2_second_scatter == nullptr )
 {
  fHits[ 0 ] = hit_1_first_scatter;
  fHits[ 1 ] = hit_1_second_scatter;
  fHits[ 2 ] = hit_2_first_scatter;
 }
 else if ( hit_1_first_scatter != nullptr && hit_1_second_scatter  == nullptr && hit_2_first_scatter != nullptr && hit_2_second_scatter != nullptr )
 {
  fHits[ 0 ] = hit_1_first_scatter;
  fHits[ 1 ] = hit_2_first_scatter;
  fHits[ 2 ] = hit_2_second_scatter;
 }
 else
 {
  return false;
 }
 return true;
}

bool REAnalysis::conditionHitsScintilators()
{
 TVector3 s1, s2, s3;
 s1 = fHits[ 0 ]->getScintilatorPosition();
 s2 = fHits[ 1 ]->getScintilatorPosition();
 s3 = fHits[ 2 ]->getScintilatorPosition();

 return s1 != s2 && s1 != s3 && s2 != s3;
}

void REAnalysis::setEnergyDepositionCondition( double energy_threshold ) { fEnergyThreshold = energy_threshold; }

bool REAnalysis::conditionHitsEnergyDeposition()
{
 double energy_deposited, energy_threshold;
 for ( unsigned int n = 0; n < 3; ++n )
 {
  energy_deposited = fHits[ n ]->getEnergyDeposition();
  energy_threshold = kUseSmearingEnergyThreshold ? getSmearedEnergyThreshold() : fEnergyThreshold;
  if ( !( energy_deposited > energy_threshold && energy_deposited < 350.0 ) )
   return false;
 }
 return true;
}

bool REAnalysis::conditionHitsZPosition()
{
 double z;
 for ( unsigned int n = 0; n < 3; ++n )
 {
  z = fHits[ n ]->getHitPosition().z();
  if ( kZMinValue > z && z > kZMaxValue )
   return false;
 }
 return true; 
}
