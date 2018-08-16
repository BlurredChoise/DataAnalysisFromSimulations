#ifndef TXTModelReader_h
#define TXTModelReader_h

#include <vector>
#include <JPetUserTask/JPetUserTask.h>
#include <JPetMCHit/JPetMCHit.h>
#include <JPetHit/JPetHit.h>
#include <JPetMCDecayTree/JPetMCDecayTree.h>
#include <JPetGeantScinHits/JPetGeantScinHits.h>
#include <JPetGeantEventPack/JPetGeantEventPack.h>
#include <JPetGeomMapping/JPetGeomMapping.h>
#include "../../Tools/ToolsForG4MC/G4MCHitData/G4MCHitData.h"
#include <JPetGeantEventInformation/JPetGeantEventInformation.h>
#include "TXTModels/TXTModel.h"
#include "../../Tools/ToolsForG4MC/G4MCReader/G4MCReader.h"

class JPetWriter;

#ifdef __CINT__
//when cint is used instead of compiler, override word is not recognized
//nevertheless it's needed for checking if the structure of project is correct
#   define override
#endif

 /**
  * Author: Mateusz Bała
  * E-mail: bala.mateusz@gmail.com
  * About class: Class read data from Monte Carlo simluation created by Geant4. This class is mother class for other classes respoble for analysis of this kind of data.
  */
class TXTModelReader: public ToolsForG4MC::G4MCReader
{
 public:
  TXTModelReader(const char* name);
  virtual ~TXTModelReader();
  virtual bool init() override;
  virtual bool exec() override;
  virtual bool terminate() override;

 private: 
  bool initModel();  
  void callModel();
  void deleteModel();
  
 private:
  TXTModel* fModel = nullptr;
  std::string kModelNameParamKey = "TXTModelReader_ModelName";
  std::string kOuputFileNameParamKey = "TXTModelReader_OuputFileTitle";
  std::string kEventsNumberToSaveParamKey = "TXTModelReader_EventsNumberToSave";
 
};

#endif
