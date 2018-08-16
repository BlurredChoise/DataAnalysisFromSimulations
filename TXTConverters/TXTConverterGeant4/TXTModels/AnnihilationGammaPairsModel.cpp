#include<iostream>
#include "AnnihilationGammaPairsModel.h"
#include "TVector3.h"
#include "TFile.h"
#include "../../../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../../../Tools/ToolsForROOT/ReadAndSave.h"
#include "TMath.h"


AnnihilationGammaPairsModel::AnnihilationGammaPairsModel() { initControlHistograms(); }

AnnihilationGammaPairsModel::~AnnihilationGammaPairsModel() { deleteControlHistograms(); }

void AnnihilationGammaPairsModel::saveControlHistograms()
{
 std::string file_name = getControlHistogramsFileName();
 TFile* file = ToolsForROOT::ReadAndSave::createFile( file_name, true ); 

 if ( !file )
  return;

 std::cout << "Saving histograms .. " << std::endl;
 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDeposition );
 ToolsForROOT::ReadAndSave::saveToFile( file, h1TimeDifference );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionXY );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionXZ );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionYZ );

 ToolsForROOT::ReadAndSave::closeFile( file );

 setHitogramsStatusAsSaved( true );
 displayStatus();
}

void AnnihilationGammaPairsModel::initControlHistograms()
{
 h1EnergyDeposition = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDeposition", 371 * 4, -0.5, 370.5, "#Delta E [keV]", "Counts" );
 h1TimeDifference = ToolsForROOT::HistogramsCreator::getTH1F( "h1TimeDifference", 4 * 100, -0.5, 4.5, "#Delta t_{12} [ns]", "Counts" );
 h2HitPositionXY = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXY", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "y [cm]" );
 h2HitPositionXZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "z [cm]" );
 h2HitPositionYZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionYZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "y [cm]", "z [cm]" );
}

void AnnihilationGammaPairsModel::deleteControlHistograms()
{
 if ( areHistogramsSavedToFile() )
  return;

 delete h1EnergyDeposition;
 delete h1TimeDifference;
 delete h2HitPositionXY;
 delete h2HitPositionXZ;
 delete h2HitPositionYZ;
}


void AnnihilationGammaPairsModel::analyzeHitsSet( std::vector< ToolsForG4MC::G4MCHitData >* data )
{
 if ( !isTXTFileOpened() )
  openTXTFile();
 
 if ( data->size() < 2 )
  return;

 TVector3 hit_position_track_1;
 TVector3 hit_position_track_2;
 bool track_1_scattered = false, track_2_scattered = false;

 int trackID = 0;
 double energy_deposition_track_1 = 0,  energy_deposition_track_2 = 0;
 double time_track_1 = 0, time_track_2 = 0;

 for( std::vector< ToolsForG4MC::G4MCHitData >::iterator it = data->begin(); it != data->end(); ++it )
 {
  trackID = it->getTrackID();
  if ( trackID == 1 && !track_1_scattered )
  {
   track_1_scattered = true;
   hit_position_track_1 = it->getHitPosition();
   energy_deposition_track_1 = it->getEnergyDeposition();
   time_track_1 = it->getTime();
  }
  else if ( trackID == 2 && !track_2_scattered )
  {
   track_2_scattered = true;
   hit_position_track_2 = it->getHitPosition();
   energy_deposition_track_2 = it->getEnergyDeposition();
   time_track_2 = it->getTime();
  }
 }

 if ( !( track_1_scattered && track_2_scattered ) )
  return;

 noticeNextEvent();

 double time_difference = TMath::Abs( time_track_1 - time_track_2 );
 h1EnergyDeposition->Fill( energy_deposition_track_1 );
 h1EnergyDeposition->Fill( energy_deposition_track_2 );
 h1TimeDifference->Fill( time_difference );

 double x1, x2, y1, y2, z1, z2;
 x1 = hit_position_track_1.x();
 x2 = hit_position_track_2.x();
 y1 = hit_position_track_1.y();
 y2 = hit_position_track_2.y();
 z1 = hit_position_track_1.z();
 z2 = hit_position_track_2.z();


 h2HitPositionXY->Fill( x1, y1 );
 h2HitPositionXY->Fill( x2, y2 );
 h2HitPositionXZ->Fill( x1, z1 );
 h2HitPositionXZ->Fill( x2, z2 );
 h2HitPositionYZ->Fill( y1, z1 );
 h2HitPositionYZ->Fill( y2, z2 );

 ( *getTXTFile() ) << x1 << " " << y1 << " " << z1 << " " << x2 << " " << y2 << " " << z2 << " " << time_difference << std::endl;
}
