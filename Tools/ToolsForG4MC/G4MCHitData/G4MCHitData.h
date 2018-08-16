#ifndef HitData_h
#define HitData_h
#include "../../ToolsForAnalysis/AnalysisData.h"
#include "TVector3.h"

namespace ToolsForG4MC {
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class represent data for analysis
File: HitData.h
**/

 class G4MCHitData : public ToolsForAnalysis::AnalysisData
 {
  public:
   enum GammaKind { Prompt = 0, ParaPositronium = 1, OrtoPositronium = 2 };

   G4MCHitData();
   virtual ~G4MCHitData();

   void setEnergyDeposition( const double& energy );
   double getEnergyDeposition() const;

   void setEventID( const int& eventID );
   int getEventID() const;

   void setTrackID( const int& trackID );
   int getTrackID() const;

   void setHitPosition( const TVector3& hit_position );
   TVector3 getHitPosition() const;

   void setScintilatorPosition( const TVector3& sci_position );
   TVector3 getScintilatorPosition() const;

   void setTime( const double& time );
   double getTime() const;

   void setScatteringIndex( const unsigned int index );
   unsigned int getScatteringIndex() const;

   void setGammaKind( GammaKind kind );
   GammaKind getGammaKind() const;
  
  private:
   double fEnergyDeposition; // [keV]
   int fEventID;
   int fTrackID;
   TVector3 fHitPosition; //[(cm, cm, cm)]
   TVector3 fScintilatorPosition; //[(cm, cm, cm)]
   double fTime; //[ns]
   unsigned int fScatteringIndex;
   GammaKind fGammaKind;
 };
};

#endif

