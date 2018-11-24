#include "TwoAnnihilationsHitsPerEventTimeSmearedModel.h"
#include "TVector3.h"
#include "TFile.h"
#include "../../../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../../../Tools/ToolsForROOT/ReadAndSave.h"

TwoAnnihilationsHitsPerEventTimeSmearedModel::TwoAnnihilationsHitsPerEventTimeSmearedModel() 
{ 
 initHistograms();
 fRandGen.initGenerator();
}
TwoAnnihilationsHitsPerEventTimeSmearedModel::~TwoAnnihilationsHitsPerEventTimeSmearedModel() { deleteHistograms(); }

void TwoAnnihilationsHitsPerEventTimeSmearedModel::analyzeEntry()
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

void TwoAnnihilationsHitsPerEventTimeSmearedModel::setCreator( TXTDataCreator* creator ) { fCreator = creator; }

void TwoAnnihilationsHitsPerEventTimeSmearedModel::setOutputFileName( std::string output_file_name ) 
{
 fTXTFileName = output_file_name + ".txt";
 fControlROOTFileName = output_file_name + "_control_histograms.root";
}

void TwoAnnihilationsHitsPerEventTimeSmearedModel::setEventsNumberToSave( unsigned int events_to_generate ) { fEventsNumberToSave = events_to_generate; }

void TwoAnnihilationsHitsPerEventTimeSmearedModel::initHistograms()
{
 double sigma = ps( kTimeSigma );

 h1EnergyDeposition = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDeposition", 371 * 4, -0.5, 370.5, "#Delta E [keV]", "Counts" );
 h1TimeDifference = ToolsForROOT::HistogramsCreator::getTH1F( "h1TimeDifference", 6 * 100, -3.0 * sigma, 3.0 * sigma, "#Delta T_{12} [ps]", "Counts" );
 h2HitPositionXY = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXY", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "y [cm]" );
 h2HitPositionXZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "z [cm]" );
 h2HitPositionYZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionYZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "y [cm]", "z [cm]" );
 h1Energy = ToolsForROOT::HistogramsCreator::getTH1F( "h1Energy", 601, -0.5, 600.5, "E [keV]", "Counts" );
 h1ScattersNumber = ToolsForROOT::HistogramsCreator::getTH1F( "h1ScattersNumber", 21, -0.5, 20.5, "Scatters number", "Counts" );
 h1Times = ToolsForROOT::HistogramsCreator::getTH1F( "h1Times", 1000, 0.0, 20000.0, "TOF [ps]", "Counts" );
}

void TwoAnnihilationsHitsPerEventTimeSmearedModel::deleteHistograms()
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

void TwoAnnihilationsHitsPerEventTimeSmearedModel::saveHistograms()
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
 ToolsForROOT::ReadAndSave::saveToFile( file, h1Times );
 fHistogramSavedToFile = true;
 ToolsForROOT::ReadAndSave::closeFile( file );

 std::cout << "Saved " << fCurrentEventsNumberSaved << " events from " << fEventsNumberToSave << " required " << std::endl;
 double status = 100.0 * static_cast<double>( fCurrentEventsNumberSaved ) / static_cast<double>( fEventsNumberToSave );
 std::cout << " Task accomplished in " << status << " percents" << std::endl;

 std::cout << "fTotalEventsNumber = " << fTotalEventsNumber << std::endl;
 std::cout << "fFirstFilter = " << fFirstFilter << std::endl;
 std::cout << "fSecondFilter = " << fSecondFilter << std::endl;
 //std::cout << "fThirdFilter = " << fThirdFilter << std::endl;

}

void TwoAnnihilationsHitsPerEventTimeSmearedModel::fillHistograms( TXTData& data )
{
 TVector3 hit = data.getHitPosition();
 double energy_deposition = data.getEnergyDeposition();

 h1EnergyDeposition->Fill( energy_deposition );
 h2HitPositionXY->Fill( hit.x(), hit.y() );
 h2HitPositionXZ->Fill( hit.x(), hit.z() );
 h2HitPositionYZ->Fill( hit.y(), hit.z() );
 h1Energy->Fill( data.getEnergy() );
}

void TwoAnnihilationsHitsPerEventTimeSmearedModel::analyzeEvent()
{

 ++fTotalEventsNumber;

 if ( !conditionHitsNumber() )
  return;

 ++fFirstFilter;

 if ( !conditionHitsKind() )
  return;

 ++fSecondFilter;

 //if ( !conditionHitsScintilators() )
 // return;

 //++fThirdFilter;


 if ( !fIsOpenedTXTFile)
 {
  fTXTFile.open( fTXTFileName.c_str(), std::ios::out );
  fIsOpenedTXTFile = true;
 }

 ++fCurrentEventsNumberSaved;

 TVector3 hit1 = fHitTrack1.getHitPosition();
 TVector3 hit2 = fHitTrack2.getHitPosition();
 double t1 = ps( getSmearedTime( fHitTrack1.getTime() ) );
 double t2 = ps( getSmearedTime( fHitTrack2.getTime() ) );

 fTXTFile << hit1.x() << " " << hit1.y() << " " << hit1.z() << " " << t1 << " " << hit2.x() << " " << hit2.y() << " " << hit2.z() << " " << t2 << std::endl;

 fillHistograms( fHitTrack1 );
 fillHistograms( fHitTrack2 );
 h1TimeDifference->Fill(  t2 - t1  );
 h1Times->Fill( t1 );
 h1Times->Fill( t2 );
}

double TwoAnnihilationsHitsPerEventTimeSmearedModel::getSmearedTime( const double& time ) const
{
 return TMath::Abs( fRandGen.getValueFromNormalDistribution( time, kTimeSigma ) );
}

double TwoAnnihilationsHitsPerEventTimeSmearedModel::ps( const double& time_ns ) const
{
 return 1000.0 * time_ns;
}

bool TwoAnnihilationsHitsPerEventTimeSmearedModel::conditionHitsNumber() { return fDatas.size() >= kRequiredHitsNumber; }

bool TwoAnnihilationsHitsPerEventTimeSmearedModel::conditionHitsScintilators()
{
 TVector3 sci1 = fHitTrack1.getScintilatorPosition();
 TVector3 sci2 = fHitTrack2.getScintilatorPosition();

 return sci1 != sci2;
}

bool TwoAnnihilationsHitsPerEventTimeSmearedModel::conditionHitsKind()
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
