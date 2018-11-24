#include "GlobalActorConverter.h"
#include "TFile.h"
#include "TTree.h"
#include <cassert>
#include <stdexcept>

GlobalActorConverter::GlobalActorConverter()
{
}

GlobalActorConverter::~GlobalActorConverter()
{
}

void GlobalActorConverter::transformToEventTree( const std::string &inFileName, const std::string &outFileName )
{
 TFile fileOut( outFileName.c_str(), "RECREATE");
 TTree *tree = new TTree( "T", "T" );
 JPetGATEEvent *event = nullptr;
 tree->Branch( "JPetGATEEvent", &event, 16000, 99 );
 try 
 {
  event = new JPetGATEEvent;
  ToolsForGATE::GlobalActorReader gar;
  if ( gar.loadFile( inFileName.c_str() ) )
  {
   bool isNewEvent = false;
   bool isFirstEvent = false;
   auto previousID = event->fEventID;
   auto currentID = previousID;
   
   while ( gar.read() )
   {
    currentID = gar.getEventID();
    isFirstEvent = ( previousID < 0 ) && ( currentID > 0 );
    isNewEvent = currentID != previousID;

    if ( isFirstEvent )
    {
     addEntryToEvent( gar, event );
    } 
    else
    {
     if ( isNewEvent )
     {
      tree->Fill();
      clearEvent( event );
     }

     addEntryToEvent( gar, event );
    }
    
    previousID = currentID;
   }
   
   if ( event->fEventID > 0 )
   {
    tree->Fill();
    clearEvent( event );
   }
  }
  else
  {
   std::cerr << "Loading file failed." << std::endl;
  }
 } 
 catch ( const std::logic_error &e )
 {
  std::cerr << e.what() << std::endl;
 } 
 catch ( ... )
 {
  std::cerr << "Udefined exception" << std::endl;
 }

 fileOut.cd();
 assert( tree );
 fileOut.Write();
}

void GlobalActorConverter::addEntryToEvent( const ToolsForGATE::GlobalActorReader &gar, JPetGATEEvent *outEvent )
{
 assert(outEvent);
 outEvent->fEventID = gar.getEventID();

 JPetGATETrackInteraction trkStep;
 trkStep.fHitPosition = gar.getProcessPosition() * 0.1;
 trkStep.fEnergyDeposition = gar.getEnergyLossDuringProcess();
 trkStep.fEnergyBeforeProcess = gar.getEnergyBeforeProcess();
 trkStep.fVolumeName = gar.getVolumeName();
 trkStep.fPolarizationBeforeProcess = gar.getPolarizationBeforeProcess();
 trkStep.fMomentumBeforeProcess = gar.getMomentumDirectionBeforeProcess();
 trkStep.fLocalTime = gar.getLocalTime() * 1000.0;
 //trkStep.fGlobalTime = gar.getGlobalTime();
 trkStep.fVolumeCenter = gar.getScintilatorPosition() * 0.1;

 int currentTrackID = gar.getTrackID();
 if ( !outEvent->fTracks.empty() )
 {
  auto &lastTrack = outEvent->fTracks.back();
  if ( lastTrack.fTrackID == currentTrackID )
  {
   lastTrack.fTrackInteractions.push_back( trkStep );
  }
  else
  {
   JPetGATETrack trk;
   trk.fEmissionEnergy = gar.getEmissionEnergyFromSource();
   trk.fTrackID = currentTrackID;
   trk.fTrackInteractions.push_back( trkStep );
   outEvent->fTracks.push_back( trk );
  }
 }
 else
 {
  JPetGATETrack trk;
  trk.fEmissionEnergy = gar.getEmissionEnergyFromSource();
  trk.fTrackID = currentTrackID;
  trk.fTrackInteractions.push_back( trkStep );
  outEvent->fTracks.push_back( trk );
 }
}

void GlobalActorConverter::clearEvent( JPetGATEEvent *outEvent )
{
 assert( outEvent );
 outEvent->fEventID = -1;
 outEvent->fTracks.clear();
}
