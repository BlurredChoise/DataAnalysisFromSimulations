#ifndef REData_h
#define REData_h
#include "../Tools/ToolsForAnalysis/AnalysisData.h"
#include "TVector3.h"

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class represent data for analysis
File: REData.h
**/
class REData : public ToolsForAnalysis::AnalysisData
{
 public:
  REData();
  virtual ~REData();

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

  void setCorrectedTime( const double& time );
  double getCorrectedTime();

  void setScatteringIndex( const unsigned int index );
  unsigned int getScatteringIndex() const;
  
 private:
  double fEnergyDeposition; // [keV]
  int fEventID;
  int fTrackID;
  TVector3 fHitPosition; //[(cm, cm, cm)]
  TVector3 fScintilatorPosition; //[(cm, cm, cm)]
  double fTime; //[ns]
  double fCorrectedTime;//[ns]
  unsigned int fScatteringIndex;
  
};

#endif

