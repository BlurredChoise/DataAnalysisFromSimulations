#include <iostream>
#include <JPetWriter/JPetWriter.h>
#include <JPetAnalysisTools/JPetAnalysisTools.h>
#include <JPetOptionsTools/JPetOptionsTools.h>
#include "../../Tools/ToolsForG4MC/G4MCReader/G4MCReader.h"
#include "TXTModelReader.h"

#include "TXTModels/TXTModel.h"
#include "TXTModels/AnnihilationGammaPairsModel.h"
#include "TXTModels/ThreeHitsEventsOnlyModel.h"

using namespace jpet_options_tools;

TXTModelReader::TXTModelReader( const char* name ) : ToolsForG4MC::G4MCReader( name ) { }

TXTModelReader::~TXTModelReader() { deleteModel(); }

bool TXTModelReader::init()
{
 INFO( "TXTModelReader started." );
 if( !ToolsForG4MC::G4MCReader::init() )
  return false;
 if ( !initModel() )
  return false;
 return true;
}

bool TXTModelReader::exec()
{ 
 if ( fModel != nullptr && !fModel->isRequiredEventsNumber() && ToolsForG4MC::G4MCReader::exec() )
  callModel();
 else
  return false;
 return true;
}

bool TXTModelReader::terminate() { return ToolsForG4MC::G4MCReader::terminate(); }

bool TXTModelReader::initModel() 
{
 bool commands_enable = isOptionSet( fParams.getOptions(), kModelNameParamKey ) && isOptionSet( fParams.getOptions(), kOuputFileNameParamKey ) && isOptionSet( fParams.getOptions(), kEventsNumberToSaveParamKey );

 if ( !commands_enable )
  return false;

 std::string model_name = getOptionAsString( fParams.getOptions(), kModelNameParamKey );
 std::string txt_ouput_file_name = getOptionAsString( fParams.getOptions(), kOuputFileNameParamKey );
 unsigned int number_of_events_to_save = static_cast< unsigned int >( getOptionAsInt( fParams.getOptions(), kEventsNumberToSaveParamKey ) );

 if ( model_name == "AnnihilationGammaPairs" )
  fModel = new AnnihilationGammaPairsModel();
 else if ( model_name == "3HitsOnly" )
  fModel = new ThreeHitsEventsOnlyModel();

 if ( fModel == nullptr )
  return false;

 fModel->setOutputFileName( txt_ouput_file_name );
 fModel->setRequiredNumberOfEventsToSave( number_of_events_to_save );

 return true;
}


void TXTModelReader::callModel() { fModel->analyzeHitsSet( ToolsForG4MC::G4MCReader::getHitsData() ); }

void TXTModelReader::deleteModel()
{
 if ( fModel != nullptr )
 {
  fModel->saveControlHistograms();
  delete fModel;
 }
}
