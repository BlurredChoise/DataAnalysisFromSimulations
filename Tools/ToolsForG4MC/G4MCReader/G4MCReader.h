#ifndef G4MCReader_h
#define G4MCReader_h

#include <vector>
#include <JPetUserTask/JPetUserTask.h>
#include <JPetMCHit/JPetMCHit.h>
#include <JPetHit/JPetHit.h>
#include <JPetMCDecayTree/JPetMCDecayTree.h>
#include <JPetGeantScinHits/JPetGeantScinHits.h>
#include <JPetGeantEventPack/JPetGeantEventPack.h>
#include <JPetGeomMapping/JPetGeomMapping.h>
#include "../G4MCHitData/G4MCHitData.h"
#include <JPetGeantEventInformation/JPetGeantEventInformation.h>

class JPetWriter;

#ifdef __CINT__
//when cint is used instead of compiler, override word is not recognized
//nevertheless it's needed for checking if the structure of project is correct
#   define override
#endif

namespace ToolsForG4MC
{
 /**
  * Author: Mateusz Bała
  * E-mail: bala.mateusz@gmail.com
  * About class: Class read data from Monte Carlo simluation created by Geant4. This class is mother class for other classes respoble for analysis of this kind of data.
  */
 class G4MCReader: public JPetUserTask
 {

  public:
   G4MCReader(const char* name);
   virtual ~G4MCReader();
   virtual bool init() override;
   virtual bool exec() override;
   virtual bool terminate() override;
   std::vector< G4MCHitData >* getHitsData();

  protected:
   void processMonteCarloEvent(JPetGeantEventPack* event_pack );
   G4MCHitData convertData( JPetGeantScinHits* raw_hit_data );

  protected :
   JPetGeomMapping* fDetectorMap = nullptr;

   std::vector< G4MCHitData > fHitsFromMonteCarlo; 

  private:
   int fLastTrackID = 0;
   int fLastEventID = -1;
   unsigned int fScatteringIndex = 0;
 };
};

#endif
