#include<iostream>
#include "ThreeHitsEventsOnlyModel.h"
#include "TVector3.h"
#include "TFile.h"
#include "../../../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../../../Tools/ToolsForROOT/ReadAndSave.h"
#include "TMath.h"


ThreeHitsEventsOnlyModel::ThreeHitsEventsOnlyModel() { initControlHistograms(); }

ThreeHitsEventsOnlyModel::~ThreeHitsEventsOnlyModel() { deleteControlHistograms(); }

void ThreeHitsEventsOnlyModel::saveControlHistograms()
{
 std::string file_name = getControlHistogramsFileName();
 TFile* file = ToolsForROOT::ReadAndSave::createFile( file_name, true ); 

 if ( !file )
  return;

 std::cout << "Saving histograms .. " << std::endl;
 ToolsForROOT::ReadAndSave::saveToFile( file, h1EnergyDeposition );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionXY );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionXZ );
 ToolsForROOT::ReadAndSave::saveToFile( file, h2HitPositionYZ );

 ToolsForROOT::ReadAndSave::closeFile( file );

 setHitogramsStatusAsSaved( true );
 displayStatus();
}

void ThreeHitsEventsOnlyModel::initControlHistograms()
{
 h1EnergyDeposition = ToolsForROOT::HistogramsCreator::getTH1F( "h1EnergyDeposition", 371 * 4, -0.5, 370.5, "#Delta E [keV]", "Counts" );
 h2HitPositionXY = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXY", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "y [cm]" );
 h2HitPositionXZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionXZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "x [cm]", "z [cm]" );
 h2HitPositionYZ = ToolsForROOT::HistogramsCreator::getTH2F( "h2HitPositionYZ", 121 * 4, -60.5, 60.5, 121 * 4, -60.5, 60.5, "y [cm]", "z [cm]" );
}

void ThreeHitsEventsOnlyModel::deleteControlHistograms()
{
 if ( areHistogramsSavedToFile() )
  return;

 delete h1EnergyDeposition;
 delete h2HitPositionXY;
 delete h2HitPositionXZ;
 delete h2HitPositionYZ;
}

void ThreeHitsEventsOnlyModel::analyzeHitsSet( std::vector< ToolsForG4MC::G4MCHitData >* data )
{
 if ( !isTXTFileOpened() )
  openTXTFile();
 
 if ( data->size() < 3 )
  return;

 std::vector<ToolsForG4MC::G4MCHitData> foundHits;
 foundHits.resize(3);
 unsigned int index = 0;

 for ( std::vector<ToolsForG4MC::G4MCHitData>::iterator it = data->begin(); it != data->begin() + 3; ++it )
   foundHits[ index++ ] = *it;

 bool scintilators_different =  foundHits[ 0 ].getScintilatorPosition() != foundHits[ 1 ].getScintilatorPosition() && foundHits[ 0 ].getScintilatorPosition() != foundHits[ 2 ].getScintilatorPosition();
 scintilators_different = scintilators_different && foundHits[ 1 ].getScintilatorPosition() != foundHits[ 2 ].getScintilatorPosition();

 if ( !scintilators_different )
  return;

 noticeNextEvent();

 TVector3 k;
 double dE, t;
 int eID, tID;

 for ( std::vector<ToolsForG4MC::G4MCHitData>::iterator it = foundHits.begin(); it != foundHits.end(); ++it )
 {
  eID = it->getEventID();
  tID = it->getTrackID();
  dE = it->getEnergyDeposition();
  t = it->getTime();
  k = it->getHitPosition();

  h1EnergyDeposition->Fill( dE );
  h2HitPositionXY->Fill( k.x(), k.y() );
  h2HitPositionXZ->Fill( k.x(), k.z() );
  h2HitPositionYZ->Fill( k.y(), k.z() );
  ( *getTXTFile() ) << eID << " " << tID << " " << k.x() << " " << k.y() << " " << k.z() << " " << t << " " << dE << std::endl;
 }
}

