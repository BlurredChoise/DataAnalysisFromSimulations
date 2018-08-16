#include <iostream>
#include "TXTDataCreator.h"
#include "../../Tools/ToolsForGATE/GlobalActorReader/GlobalActorReader.h"
#include "TXTModels/TXTModel.h"
#include "TXTModels/ThreeHitsPerEventModel.h"
#include <cstdlib>
#include <string>

TXTModel* getModel( std::string model_name )
{
 if ( model_name == "3HitsEvent" )
  return new ThreeHitsPerEventModel();
 return nullptr;
}


int main(int argc, char *argv[])
{
 if ( argc < 5 )
 {
  std::cout << "Inccorect number of parameters" << std::endl;
  return 1;
 }
 
 std::string input_file_name( argv[ 1 ] );
 std::string output_file_name( argv[ 2 ] );
 std::string model_name( argv[ 3 ] );
 unsigned int numbers_of_events_to_save = static_cast< unsigned int >( atoi( argv[ 4 ] ) );

 TXTModel* model = getModel( model_name );
 model->setEventsNumberToSave( numbers_of_events_to_save );
 model->setEventsNumberToSave( numbers_of_events_to_save );

 if ( model == nullptr )
 {
  std::cout << "Model couldn't be initialized" << std::endl;
  return 2;
 }

 TXTDataCreator data_creator;

 ToolsForGATE::GlobalActorReader gar;

 model->setCreator( &data_creator );
 data_creator.setReader( &gar );

 gar.execute( input_file_name, model, &data_creator );
 model->saveHistograms();
 delete model;
}
