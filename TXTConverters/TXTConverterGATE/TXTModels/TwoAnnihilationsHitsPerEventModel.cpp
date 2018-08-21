#include "TwoAnnihilationsHitsPerEventModel.h"
#include "TVector3.h"
#include "TFile.h"
#include "../../../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../../../Tools/ToolsForROOT/ReadAndSave.h"

TwoAnnihilationsHitsPerEventModel::TwoAnnihilationsHitsPerEventModel() { initHistograms(); }
TwoAnnihilationsHitsPerEventModel::~TwoAnnihilationsHitsPerEventModel() { deleteHistograms(); }

void TwoAnnihilationsHitsPerEventModel::analyzeEntry()
{
 if ( fCurrentEventsNumberSaved == fEventsNumberToSave )
 {
  fCreator->stopJob();
  return;
 }

 TXTData data = *( dynamic_cast< TXTData* >( fCreator->getData() ) );
 if ( data.getEventID() != fEventID )
 {
  if ( fEventID > -1 )
   analyzeEvent();
  fEventID = data.getEventID();
  fDatas.clear();
 }
 fDatas.push_back( data );
}

void TwoAnnihilationsHitsPerEventModel::setCreator( TXTDataCreator* creator ) { fCreator = creator; }

void TwoAnnihilationsHitsPerEventModel::setOutputFileName( std::string output_file_name ) 
{
 fTXTFileName = output_file_name + ".txt";
 fControlROOTFileName = output_file_name + "_control_histograms.root";
}

void TwoAnnihilationsHitsPerEventModel::setEventsNumberToSave( unsigned int events_to_generate ) { fEventsNumberToSave = events_to_generate; }

void TwoAnnihilationsHitsPerEventModel::initHistograms()
{
 h1EnergyDeposition = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDeposition", 371 * 4, -0.5, 370.5, "#Delta E [keV]", "Counts" );
 h1TimeDifference = ToolsForROOT::HistogramsCreator::getTH1F( "h1TimeDifference", 3 * 100, -1.5, 1.5, "#Delta T_{12} [ns]", "Counts" );
 h2HitPositionXY = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXY", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "y [cm]" );
 h2HitPositionXZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "z [cm]" );
 h2HitPositionYZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionYZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "y [cm]", "z [cm]" );
 h1Energy = ToolsForROOT::HistogramsCreator::getTH1F( "h1Energy", 601, -0.5, 600.5, "E [keV]", "Counts" );
 h1ScattersNumber = ToolsForROOT::HistogramsCreator::getTH1F( "h1ScattersNumber", 21, -0.5, 20.5, "Scatters number", "Counts" );
}

void TwoAnnihilationsHitsPerEventModel::deleteHistograms()
{
 if( fIsOpenedTXTFile )
  fTXTFile.close();

 if ( fHistogramSavedToFile )
  return;
 delete h1EnergyDeposition;
 delete h1TimeDifference;
 delete h2HitPositionXY;
 delete h2HitPositionXZ;
 delete h2HitPositionYZ;
 delete h1Energy;
 delete h1ScattersNumber;
}

void TwoAnnihilationsHitsPerEventModel::saveHistograms()
{
 TFile* file = ToolsForROOT::ReadAndSave::createFile( fControlROOTFileName, true ); 
 if ( !file )
  return;

 std::cout << "Saving histograms .. " << std::endl;
 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDeposition );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1TimeDifference ); 
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionXY );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionXZ );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionYZ );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1Energy );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1ScattersNumber );
 fHistogramSavedToFile = true;
 ToolsForROOT::ReadAndSave::closeFile( file );

 std::cout << "Saved " << fCurrentEventsNumberSaved << " events from " << fEventsNumberToSave << " required " << std::endl;
 double status = 100.0 * static_cast<double>( fCurrentEventsNumberSaved ) / static_cast<double>( fEventsNumberToSave );
 std::cout << " Task accomplished in " << status << " percents" << std::endl;

 std::cout << "fTotalEventsNumber = " << fTotalEventsNumber << std::endl;
 std::cout << "fFirstFilter = " << fFirstFilter << std::endl;
 std::cout << "fSecondFilter = " << fSecondFilter << std::endl;
 std::cout << "fThirdFilter = " << fThirdFilter << std::endl;
 std::cout << "fFourthFilter = " << fFourthFilter << std::endl;

}

void TwoAnnihilationsHitsPerEventModel::fillHistograms( TXTData& data )
{
 TVector3 hit = data.getHitPosition();
 double energy_deposition = data.getEnergyDeposition();

 h1EnergyDeposition->Fill( energy_deposition );
 h2HitPositionXY->Fill( hit.x(), hit.y() );
 h2HitPositionXZ->Fill( hit.x(), hit.z() );
 h2HitPositionYZ->Fill( hit.y(), hit.z() );
 h1Energy->Fill( data.getEnergy() );
}

void TwoAnnihilationsHitsPerEventModel::analyzeEvent()
{

 ++fTotalEventsNumber;

 if ( !conditionHitsNumber() )
  return;

 ++fFirstFilter;

 if ( !conditionHitsKind() )
  return;

 ++fSecondFilter;

 if ( !conditionHitsScintilators() )
  return;

 ++fThirdFilter;

 if ( !conditionEnergyBeforeScattering() )
  return;

 ++fFourthFilter;

 /*bool passed = conditionHitsNumber() && conditionHitsKind() && conditionHitsScintilators();

 if( !passed )
  return;*/

 if ( !fIsOpenedTXTFile)
 {
  fTXTFile.open( fTXTFileName.c_str(), std::ios::out );
  fIsOpenedTXTFile = true;
 }

 ++fCurrentEventsNumberSaved;

 TVector3 hit1 = fHitTrack1.getHitPosition();
 TVector3 hit2 = fHitTrack2.getHitPosition();
 double deltaT = fHitTrack2.getTime() - fHitTrack1.getTime();

 fTXTFile << hit1.x() << " " << hit1.y() << " " << hit1.z() << " " << hit2.x() << " " << hit2.y() << " " << hit2.z() << " " << deltaT << std::endl;

 fillHistograms( fHitTrack1 );
 fillHistograms( fHitTrack2 );
 h1TimeDifference->Fill( deltaT );
}

bool TwoAnnihilationsHitsPerEventModel::conditionHitsNumber() { return fDatas.size() >= kRequiredHitsNumber; }

bool TwoAnnihilationsHitsPerEventModel::conditionHitsScintilators()
{
 TVector3 sci1 = fHitTrack1.getScintilatorPosition();
 TVector3 sci2 = fHitTrack2.getScintilatorPosition();

 return sci1 != sci2;
}

bool TwoAnnihilationsHitsPerEventModel::conditionHitsKind()
{
 bool annihilation_hit_per_track_1 = false, annihilation_hit_per_track_2 = false;
 
 for ( std::vector<TXTData>::iterator it = fDatas.begin(); it != fDatas.end(); ++it )
 {
  if ( !annihilation_hit_per_track_1 && it->getTrackID() == 1 )
  {
   fHitTrack1 = *it;
   annihilation_hit_per_track_1 = true;
  }
  else if ( !annihilation_hit_per_track_2 && it->getTrackID() == 2 )
  {
   fHitTrack2 = *it;
   annihilation_hit_per_track_2 = true;
  }
  else if ( annihilation_hit_per_track_1 && annihilation_hit_per_track_2 )
  {
   h1ScattersNumber->Fill( fHitTrack1.getScatteringIndex() );
   h1ScattersNumber->Fill( fHitTrack2.getScatteringIndex() );
   return true;
  }
 }
 return false;
}

bool TwoAnnihilationsHitsPerEventModel::conditionEnergyBeforeScattering()
{
 //Becouse there is small fluctuaction of gammas energy - something like: 510.99999999 and 511.000001 - and it normal numerical problem.
 bool e1 = TMath::Abs(511.0 - fHitTrack1.getEnergy() ) < 0.000001;
 bool e2 = TMath::Abs(511.0 - fHitTrack2.getEnergy() ) < 0.000001;

 return e1 && e2;
}
