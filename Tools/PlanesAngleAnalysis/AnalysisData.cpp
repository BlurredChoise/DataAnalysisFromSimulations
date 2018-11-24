#include "AnalysisData.h"

AnalysisData::AnalysisData() { initVariables(); }
AnalysisData::~AnalysisData() {}

void AnalysisData::initVariables()
{
 fTOT = 0;
 fReferenceTime = 0;
 fEffectiveTime = 0;
 fHitPosition = TVector3( 0, 0, 0 );
 fHitDistanceFromCenter = 0;
}

double AnalysisData::ns() { return 0.001; } // ratio between pikosecond and nanosecond

void AnalysisData::fill( const JPetHit& hit, const JPetHit& hit_reference, const bool& is_data_from_simulation )
{
 if ( is_data_from_simulation )
 {
  fDataFromSimulation = is_data_from_simulation;
  fEnergyDeposition = hit.getEnergy();
 }
 else
 {
  fTOT = calcTOT(hit);
 }

 fReferenceTime = calcReferenceTime( hit, hit_reference );
 fEffectiveTime = calcEffectiveTime( hit, hit_reference );
 fHitPosition = hit.getPos();
 fHitDistanceFromCenter = hit.getPos().Mag();
 fCorrectedTime = calcCorrectedTime( hit );
 fLambda = calcLambda( hit );
 fScintilatorId = hit.getScintillator().getID();
 fRawTime = hit.getTime() * ns();
}

double AnalysisData::calcTOT( const JPetHit& hit )
{
 double TOT_A = 0.0; //[ps]
 double TOT_B = 0.0; //[ps]

 auto lead_times_A = hit.getSignalA().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
 auto trail_times_A = hit.getSignalA().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Trailing);
 auto lead_times_B =  hit.getSignalB().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Leading);
 auto trail_times_B = hit.getSignalB().getRecoSignal().getRawSignal().getTimesVsThresholdNumber(JPetSigCh::Trailing);

 for (auto& thr_time_pair : lead_times_A)
 {
  int thr = thr_time_pair.first;
  if (trail_times_A.count(thr) > 0 ) 
    TOT_A = TOT_A + trail_times_A[thr] - lead_times_A[thr];
 }

 for (auto& thr_time_pair : lead_times_B)
 {
  int thr = thr_time_pair.first;
  if ( trail_times_B.count(thr) > 0 )
   TOT_B = TOT_B + trail_times_B[thr] - lead_times_B[thr];
 }

 return (TOT_A + TOT_B) * ns(); // [ns]
}

double AnalysisData::calcReferenceTime( const JPetHit& hit, const JPetHit& hit_reference ) 
{
 return ( hit.getTime() - hit_reference.getTime() ) * ns(); //[ns]
}

double AnalysisData::calcEffectiveTime( const JPetHit& hit, const JPetHit& hit_reference )
{
 double time_of_flight_from_system_center_to_hit_position = hit.getPos().Mag() / kLightVeclocityInVacuum; //[ns]
 double time_of_hit = hit.getTime() * ns(); //[ns]
 double time_of_flight_from_system_center_to_hit_position_ref = hit_reference.getPos().Mag() / kLightVeclocityInVacuum; //[ns]
 double time_of_hit_ref = hit_reference.getTime() * ns(); //[ns] 

 return time_of_hit - time_of_flight_from_system_center_to_hit_position - ( time_of_hit_ref - time_of_flight_from_system_center_to_hit_position_ref ); //[ns]
}

double AnalysisData::getTOT() { return fTOT; } //[ns]

double AnalysisData::getReferenceTime() { return fReferenceTime; } //[ns]

double AnalysisData::getEffectiveTime() { return fEffectiveTime; } //[ns]

TVector3 AnalysisData::getHitPosition() { return fHitPosition; } //(cm, cm, cm)

double AnalysisData::getHitDistanceFromCenter() { return fHitDistanceFromCenter; } //[cm]

double AnalysisData::calcCorrectedTime( const JPetHit& hit )
{
 double time_of_flight_from_system_center_to_hit_position = hit.getPos().Mag() / kLightVeclocityInVacuum; //[ns]
 double time_of_hit = hit.getTime() * ns(); //[ns]

 //std::cout << "AnalysisData::calcCorrectedTime:" << std::endl;
 //std::cout << "hit.getPos().Mag() = " << hit.getPos().Mag() << std::endl;
 //std::cout << "time_of_flight_from_system_center_to_hit_position = " << time_of_flight_from_system_center_to_hit_position << std::endl;
 //std::cout << "hit.getTime() = " << hit.getTime() << std::endl;
 //std::cout << "time_of_hit = " << time_of_hit << std::endl;
 
 double diff = time_of_hit - time_of_flight_from_system_center_to_hit_position;
 //std::cout << "diff = " << diff << std::endl;
 //std::cout << " ----------- " << std::endl;
 
 return diff;//time_of_hit - time_of_flight_from_system_center_to_hit_position; //[ns]
}

double AnalysisData::getCorrectedTime() const { return fCorrectedTime; }

double AnalysisData::calcLambda( const JPetHit& hit )
{
 double t =  hit.getTime() * ns() ; //[ns]
 double d = hit.getPos().Mag(); //[cm]
 return d - t * kLightVeclocityInVacuum; //[cm]
}

double AnalysisData::getLambda() { return fLambda; }

int AnalysisData::getScintilatorID() { return fScintilatorId; }

unsigned int AnalysisData::getCorrectedTimeIndex() { return fCorrectedTimeIndex; }

void AnalysisData::setCorrectedTimeIndex( unsigned int corrected_time_index ) { fCorrectedTimeIndex = corrected_time_index; }

double AnalysisData::getRawTime() { return fRawTime; }

void AnalysisData::setMotherGammaIndex( unsigned int mother_index ) { fMotherIndex = mother_index; }

unsigned int AnalysisData::getMotherGammaIndex() { return fMotherIndex; }

bool AnalysisData::isDataFromSimulation() const { return fDataFromSimulation; }

double AnalysisData::getEnergyDeposition() const { return fEnergyDeposition; }
