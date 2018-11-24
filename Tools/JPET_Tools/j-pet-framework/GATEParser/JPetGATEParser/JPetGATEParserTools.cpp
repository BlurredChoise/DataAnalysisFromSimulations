#include <JPetGATEParser/JPetGATEParserTools.h>
#include <JPetGATETrackInteraction/JPetGATETrackInteraction.h>
#include <TMath.h>

const float JPetGATEParserTools::kEnergyThreshold = 200.;
const float JPetGATEParserTools::kReferenceEnergy = 270.;
const float JPetGATEParserTools::kTimeResolutionConstant = 80.;

TRandom3 JPetGATEParserTools::fRandomGenerator = TRandom3();

JPetMCHit JPetGATEParserTools::createJPetMCHit( JPetGATETrackInteraction& gateHit, const JPetParamBank& paramBank )
{
  TVector3 hit_position( gateHit.getScintilatorPosition().x(), gateHit.getScintilatorPosition().y(), gateHit.getHitPosition().z() );
  JPetMCHit mcHit = JPetMCHit( 0, 0, gateHit.getEneDepos(), gateHit.getTime(), hit_position , gateHit.getPolarizationIn(), gateHit.getMomentumIn() );
  unsigned int scintilator_id = getScintilatorID( paramBank, gateHit.getScintilatorPosition() );
  JPetScin& scin =  paramBank.getScintillator( scintilator_id );
  mcHit.setScintillator(scin);
  mcHit.setBarrelSlot(scin.getBarrelSlot());
  return mcHit;
}

JPetHit JPetGATEParserTools::reconstructHit( JPetMCHit& mcHit, const float timeShift, const float z_resolution )
{

  JPetHit hit = dynamic_cast<JPetHit&>(mcHit);
  hit.setEnergy( addEnergySmearing(mcHit.getEnergy()) );
  // adjust to time window and smear
  hit.setTime( addTimeSmearing( -( mcHit.getTime() - timeShift ), mcHit.getEnergy() ) );
  hit.setPosZ( addZHitSmearing( hit.getPosZ(), z_resolution ) );

  return hit;

}

bool JPetGATEParserTools::isHitReconstructed(JPetHit& hit, const float th)
{
 return hit.getEnergy() >= th;
}

void JPetGATEParserTools::setGeneratorSeed(unsigned long seed)
{
  fRandomGenerator.SetSeed(seed);
}

float JPetGATEParserTools::addZHitSmearing(float zIn, float z_res)
{
  return fRandomGenerator.Gaus(zIn, z_res);
}

float JPetGATEParserTools::addEnergySmearing(float eneIn)
{
  // eneIn in keV
  float alpha = 0.044 / sqrt(eneIn / 1000.);
  return eneIn + alpha * eneIn * fRandomGenerator.Gaus(0., 1.);
}

float JPetGATEParserTools::addTimeSmearing(float timeIn, float eneIn)
{
  // eneIn in keV, timeIn in ps
  float time;

  if ( eneIn > kEnergyThreshold )
  {
    time = timeIn + kTimeResolutionConstant * fRandomGenerator.Gaus( 0., 1. );
  }
  else
  {
    time = timeIn + kTimeResolutionConstant * fRandomGenerator.Gaus( 0., 1. ) / sqrt( eneIn / kReferenceEnergy );
  }

  return time;
}

unsigned int JPetGATEParserTools::getScintilatorID( const JPetParamBank& paramBank, const TVector3& scintilator_position )
{
 for ( std::map<int, JPetScin*>::const_iterator it = paramBank.getScintillators().begin(); it != paramBank.getScintillators().end(); ++it )
 {
  TVector3 scintilator_position_from_paramBank = getScintilatorPosition( paramBank, it->second->getID() );
  if ( isTheSameScintilator( scintilator_position_from_paramBank, scintilator_position ) )
   return it->second->getID();
 }
 ERROR( "Could not find proper scintilator" );
 return 0;
}

TVector3 JPetGATEParserTools::getScintilatorPosition( const JPetParamBank& paramBank, const unsigned int& scintilator_id )
{
  double radius = paramBank.getScintillator( scintilator_id ).getBarrelSlot().getLayer().getRadius();
  double theta = TMath::DegToRad() * paramBank.getScintillator( scintilator_id ).getBarrelSlot().getTheta();
  TVector3 scintilator_position( radius * TMath::Cos( theta ), radius * TMath::Sin( theta ), 0.0 );
  return scintilator_position;
}

bool JPetGATEParserTools::isTheSameScintilator( const TVector3& s1, const TVector3& s2 )
{
 double delta_x = TMath::Abs( s1.x() - s2.x() );
 double delta_y = TMath::Abs( s1.y() - s2.y() );
 double epsilon = 0.001;
 return delta_x < epsilon && delta_y < epsilon;
}

void JPetGATEParserTools::printSci( const JPetParamBank& paramBank )
{
 for ( std::map<int, JPetScin*>::const_iterator it = paramBank.getScintillators().begin(); it != paramBank.getScintillators().end(); ++it )
 {
  TVector3 s = getScintilatorPosition( paramBank, it->second->getID() );
  INFO( "-----" );
  INFO( it->second->getID() );
  INFO( s.x() );
  INFO( s.y() );
  INFO( s.z() );
 } 
}
