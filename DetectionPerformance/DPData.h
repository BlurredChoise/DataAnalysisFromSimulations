#ifndef DPData_h
#define DPData_h
#include "../Tools/ToolsForAnalysis/AnalysisData.h"
#include "TVector3.h"
#include <string>

/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This class represent data for analysis
File: DPData.h
**/
class DPData : public ToolsForAnalysis::AnalysisData
{
 public:
  DPData();
  virtual ~DPData();

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

  void setEnergy( const double& energy);
  double getEnergy() const;

  void setEmissionEnergy( const double& energy );
  double getEmissionEnergy() const;
  
  std::string fVolumeName;

 private:
  double fEnergyDeposition; // [keV]
  int fEventID;
  int fTrackID;
  TVector3 fHitPosition; //[(cm, cm, cm)]
  TVector3 fScintilatorPosition; //[(cm, cm, cm)]
  double fTime; //[ns]
  unsigned int fScatteringIndex;
  double fEnergy;//[keV]
  double fEmissionEnergy;//[keV]
  
};

#endif

