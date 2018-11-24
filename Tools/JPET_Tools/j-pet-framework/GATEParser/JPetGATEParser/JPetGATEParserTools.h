#ifndef JPETPARSERTOOLS_H
#define JPETPARSERTOOLS_H

#ifdef __CINT__
//when cint is used instead of compiler, override word is not recognized
//nevertheless it's needed for checking if the structure of project is correct
#   define override
#endif

#include <JPetGATETrackInteraction/JPetGATETrackInteraction.h>
#include <TRandom3.h>
#include <JPetMCHit/JPetMCHit.h>
#include <JPetHit/JPetHit.h>
#include "JPetParamBank/JPetParamBank.h"
#include <TVector3.h>

class JPetGATEParserTools
{
 public:

  static JPetMCHit createJPetMCHit( JPetGATETrackInteraction& gateHit, const JPetParamBank& paramBank );
  static JPetHit reconstructHit( JPetMCHit& mcHit, const float timeShift, const float z_resolution );
  static bool isHitReconstructed( JPetHit& hit, const float th );

  static float addEnergySmearing(float eneIn );
  static float addZHitSmearing(float zIn, float z_res);
  static float addTimeSmearing(float timeIn, float eneIn);

  static void setGeneratorSeed(unsigned long seed);

  static void printSci( const JPetParamBank& paramBank );

 private:
  static unsigned int getScintilatorID( const JPetParamBank& paramBank, const TVector3& scintilator_position );
  static TVector3 getScintilatorPosition( const JPetParamBank& paramBank, const unsigned int& scintilator_id );
  static bool isTheSameScintilator( const TVector3& s1, const TVector3& s2 );

 private:
  static TRandom3 fRandomGenerator;
  static const float kEnergyThreshold;
  static const float kReferenceEnergy;
  static const float kTimeResolutionConstant;
};

#endif
