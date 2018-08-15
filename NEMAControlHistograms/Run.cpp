#include <iostream>
#include "../Tools/ToolsForGATE/GlobalActorReader/GlobalActorReader.h"
#include "TVector3.h"

#include "../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../Tools/ToolsForROOT/ReadAndSave.h"

int main(int argc, char *argv[])
{
 if ( argc < 3)
 {
  std::cout << "Inccorect number of parameters" << std::endl;
  return 1;
 }
 
 std::string input_file_name( argv[ 1 ] );
 std::string output_file_name( argv[ 2 ] );
 ToolsForGATE::GlobalActorReader gar;

 TH2F* hxy = ToolsForROOT::HistogramsCreator::getTH2F( "hxy", 1000, -20, 20, 1000, -20, 20, "x [cm]","y [cm]");
 TH2F* hxz = ToolsForROOT::HistogramsCreator::getTH2F( "hxz", 1000, -20, 20, 1000, -20, 20, "x [cm]","z [cm]");
 TH2F* hyz = ToolsForROOT::HistogramsCreator::getTH2F( "hyz", 1000, -20, 20, 1000, -20, 20, "y [cm]","z [cm]");

 TH2F* hxy_pair = ToolsForROOT::HistogramsCreator::getTH2F( "hxyPAIR", 1000, -20, 20, 1000, -20, 20, "x [cm]","y [cm]");
 TH2F* hxz_pair = ToolsForROOT::HistogramsCreator::getTH2F( "hxzPAIR", 1000, -20, 20, 1000, -20, 20, "x [cm]","z [cm]");
 TH2F* hyz_pair = ToolsForROOT::HistogramsCreator::getTH2F( "hyzPAIR", 1000, -20, 20, 1000, -20, 20, "y [cm]","z [cm]");

 int eventID = -1;
 double x,y,z;
 bool track1_scattered = false, track2_scattered = false;

 if ( !gar.loadFile( input_file_name ) )
  return 2;
 while( gar.read() )
 {
  int eID = gar.getEventID();
  if ( eID != eventID )
  {
   if ( eventID > -1 )
   {
    hxy->Fill(x,y);
    hxz->Fill(x,z);
    hyz->Fill(y,z);

    if ( track1_scattered && track2_scattered )
    {
     hxy_pair->Fill(x,y);
     hxz_pair->Fill(x,z);
     hyz_pair->Fill(y,z);
    }
   }
   eventID = eID;
   TVector3 v = gar.getEmissionPointFromSource();
   x = v.x()/10.0;
   y = v.y()/10.0;
   z = v.z()/10.0;
   track1_scattered = track2_scattered = false;
  }

  if ( gar.getTrackID() == 1 && !track1_scattered )
   track1_scattered = true;
  else if ( gar.getTrackID() == 2 && !track2_scattered )
   track2_scattered = true;
 }

 TFile* f = ToolsForROOT::ReadAndSave::createFile( output_file_name, true );

 ToolsForROOT::ReadAndSave::saveToFile( f, hxy );
 ToolsForROOT::ReadAndSave::saveToFile( f, hxz );
 ToolsForROOT::ReadAndSave::saveToFile( f, hyz );
 ToolsForROOT::ReadAndSave::saveToFile( f, hxy_pair );
 ToolsForROOT::ReadAndSave::saveToFile( f, hxz_pair );
 ToolsForROOT::ReadAndSave::saveToFile( f, hyz_pair );
 ToolsForROOT::ReadAndSave::closeFile(f);
}
