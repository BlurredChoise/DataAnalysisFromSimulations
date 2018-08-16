#include "ThreeHitsPerEventModel.h"
#include "TVector3.h"
#include "TFile.h"
#include "../../../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../../../Tools/ToolsForROOT/ReadAndSave.h"

ThreeHitsPerEventModel::ThreeHitsPerEventModel() { initHistograms(); }
ThreeHitsPerEventModel::~ThreeHitsPerEventModel() { deleteHistograms(); }

void ThreeHitsPerEventModel::analyzeEntry()
{
 if ( fCurrentEventsNumberSaved >= fEventsNumberToSave )
  return;

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

void ThreeHitsPerEventModel::setCreator( TXTDataCreator* creator ) { fCreator = creator; }

void ThreeHitsPerEventModel::setOutputFileName( std::string output_file_name ) 
{
 fTXTFileName = output_file_name + ".txt";
 fControlROOTFileName = output_file_name + "_control_histograms.root";
}

void ThreeHitsPerEventModel::setEventsNumberToSave( unsigned int events_to_generate ) { fEventsNumberToSave = events_to_generate; }

void ThreeHitsPerEventModel::initHistograms()
{
 h1EnergyDeposition = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDeposition", 371 * 4, -0.5, 370.5, "#Delta E [keV]", "Counts" );
 h2HitPositionXY = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXY", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "y [cm]" );
 h2HitPositionXZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "z [cm]" );
 h2HitPositionYZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionYZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "y [cm]", "z [cm]" );
 h3HitPositionXYZ = ToolsForROOT::HistogramsCreator::getTH3F( "h3HitPositionXYZ", 121 * 4, -60.5, 60.5, "x [cm]", "y [cm]", "z [cm]" );
 h2ScattersPerTrack = ToolsForROOT::HistogramsCreator::getTH2F( "h2ScattersPerTrack", 5, -0.5, 4.5, 5, -0.5, 4.5, "Number of scatters per track 1", "Number of scatters per track 2" );
}

void ThreeHitsPerEventModel::deleteHistograms()
{
 if ( fHistogramSavedToFile )
  return;
 delete h1EnergyDeposition;
 delete h2HitPositionXY;
 delete h2HitPositionXZ;
 delete h2HitPositionYZ;
 delete h2ScattersPerTrack;
}

void ThreeHitsPerEventModel::saveHistograms()
{
 TFile* file = ToolsForROOT::ReadAndSave::createFile( fControlROOTFileName, true ); 
 if ( !file )
  return;

 std::cout << "Saving histograms .. " << std::endl;
 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDeposition );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionXY );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionXZ );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionYZ );
 ToolsForROOT::ReadAndSave::saveToFile( file, h3HitPositionXYZ );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2ScattersPerTrack );

 fHistogramSavedToFile = true;

 std::cout << "Saved " << fCurrentEventsNumberSaved << " events from " << fEventsNumberToSave << " required ";
 double status = 100.0 * static_cast<double>( fCurrentEventsNumberSaved ) / static_cast<double>( fEventsNumberToSave );
 std::cout << " Task accomplished in " << status << " prercents";
}

void ThreeHitsPerEventModel::analyzeEvent()
{

 bool passed = conditionHitsNumber() && conditionHitsScintilators();
 if( !passed )
  return;

 if ( !fIsOpenedTXTFile)
  fTXTFile.open( fTXTFileName.c_str(), std::ios::out );

 ++fCurrentEventsNumberSaved;

 double eventID = fDatas[ 0 ].getEventID();
 double trackID, x, y, z, t, dE;
 TVector3 hit_pos;
 unsigned int scatters_per_track1 =0, scatters_per_track2 = 0;

 for ( std::vector<TXTData>::iterator it = fDatas.begin(); it != fDatas.end(); ++it )
 {
  trackID = it->getTrackID();

  if ( trackID == 1 )
   ++scatters_per_track1;
  else if ( trackID == 2 )
   ++scatters_per_track2;

  hit_pos = it->getHitPosition();
  x = hit_pos.x();
  y = hit_pos.y(); 
  z = hit_pos.z();
  t = it->getTime();
  dE = it->getEnergyDeposition();

  fTXTFile << eventID << " " << trackID << " " << x << " " << y << " " << z << " " << t << " " << dE << std::endl;

  h1EnergyDeposition->Fill( dE );
  h2HitPositionXY->Fill( x, y );
  h2HitPositionXZ->Fill( x, z );
  h2HitPositionYZ->Fill( y, z );
  h3HitPositionXYZ->Fill( x, y, z );
 }
 
 h2ScattersPerTrack->Fill( scatters_per_track1, scatters_per_track2 );
}

bool ThreeHitsPerEventModel::conditionHitsNumber() { return fDatas.size() == kRequiredHitsNumber; }

bool ThreeHitsPerEventModel::conditionHitsScintilators()
{
 TVector3 sci1 = fDatas[ 0 ].getScintilatorPosition();
 TVector3 sci2 = fDatas[ 1 ].getScintilatorPosition();
 TVector3 sci3 = fDatas[ 2 ].getScintilatorPosition();

 return sci1 != sci2 && sci1 != sci3 && sci2 != sci3;
}
