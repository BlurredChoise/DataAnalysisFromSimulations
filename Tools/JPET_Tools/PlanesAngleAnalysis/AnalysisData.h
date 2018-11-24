#ifndef ANALYSIS_DATA
#define ANALYSIS_DATA
#include <TVector3.h>
#include <JPetHit/JPetHit.h>

class AnalysisData
{
public:
 AnalysisData();
 ~AnalysisData();

 void fill( const JPetHit& hit, const JPetHit& hit_reference, const bool& is_data_from_simulation );
 double getTOT(); //[ns]
 double getReferenceTime(); //[ns]
 double getEffectiveTime(); //[ns]
 TVector3 getHitPosition(); //(cm, cm, cm)
 double getHitDistanceFromCenter(); //[cm]
 double getCorrectedTime() const; //[ns]
 double getLambda(); //[cm]
 int getScintilatorID();
 unsigned int getCorrectedTimeIndex();
 void setCorrectedTimeIndex( unsigned int corrected_time_index );
 double getRawTime();
 void setMotherGammaIndex( unsigned int mother_index );
 unsigned int getMotherGammaIndex();

 bool isDataFromSimulation() const;
 double getEnergyDeposition() const;
 
private:
 void initVariables();
 double ns(); //[1/1000] - ratio ps/ns
 double calcTOT( const JPetHit& hit); //[ns]
 double calcReferenceTime( const JPetHit& hit, const JPetHit& hit_reference ); //[ns]
 double calcEffectiveTime( const JPetHit& hit, const JPetHit& hit_reference ); //[ns]
 double calcCorrectedTime( const JPetHit& hit );//[ns]
 double calcLambda( const JPetHit& hit );

private:
 const double kLightVeclocityInVacuum = 29.979246; //[cm/ns]
 double fTOT; //ns
 //Difference between hit and refference hit (first hit in events list)
 double fReferenceTime; //ns
 //Difference between hit decreased by hit position /light speed and refference hit (first hit in events list)
 double fEffectiveTime; //ns
 //Hit position
 TVector3 fHitPosition;
 //Hit disance from center of experiment globla system - from point (0,0,0)
 double fHitDistanceFromCenter;
 //Time corrected by distance
 double fCorrectedTime; //ns
 //Lambda = |d|-c*t
 double fLambda;
 //Scintilator id
 int fScintilatorId;
 //Corrected time index - it tells us which hit earlier
 unsigned int fCorrectedTimeIndex;
 //Raw time - from JPetHit getTime [ns]
 double fRawTime;
 //Mother index - from which gamma this gamma came from
 unsigned int fMotherIndex;
 //Energy deposition
 double fEnergyDeposition;
 //Is data from simulation
 bool fDataFromSimulation = false; 

};

#endif
