#include <iostream>
#include "DPDataCreator.h"
#include "../Tools/ToolsForGATE/GlobalActorReader/GlobalActorReader.h"
#include "DPModels/EfficiencyCounter.h"
#include <cstdlib>
#include <string>
#include "../Tools/ToolsForROOT/ReadAndSave.h"

int main(int argc, char *argv[])
{

 if ( ! ( argc == 10 || argc == 12 ) )
 {
  std::cout << "Inccorect number of parameters" << std::endl;
  return 1;
 }
 
 std::string input_file_name( argv[ 1 ] );
 std::string output_file_name( argv[ 2 ] );
 std::string source_model_name( argv[ 3 ] );
 unsigned int generated_events = static_cast< unsigned int >( atoi( argv[ 4 ] ) );
 unsigned int genertaed_gammas_per_event = static_cast< unsigned int >( atoi( argv[ 5 ] ) );
 unsigned int geometry_number = static_cast< unsigned int >( atoi( argv[ 6 ] ) );
 double energy_threshold = atof( argv[ 7 ] );
 unsigned int use_prompt = static_cast<unsigned int>( atoi( argv[ 8 ] ) );
 std::string root_file_name( argv[ 9 ] );

 double prompt_energy = 0, propmt_energy_threshold = 0;

 if ( argc == 12 )
 {
  if ( use_prompt != 1 )
  {
   std::cout << "[ERROR] Try use analysis of prompt without using prompt option. Program stop!" << std::endl;
   return 2;
  }
  prompt_energy = atof( argv[ 10 ] );
  propmt_energy_threshold = atof( argv[ 11 ] );
 }

 EfficiencyCounter model;
 model.setOutputFileName( output_file_name );
 model.setSourceModelName( source_model_name );
 model.setGeometryNumber( geometry_number );
 model.setNumberOfGeneratedEvents( generated_events );
 model.setNumberOdGammasGeneratedPerEvent( genertaed_gammas_per_event );
 model.setEnergyThreshold( energy_threshold );
 if ( use_prompt == 1  )
 {
  model.setPromptVisible( true );
  model.setPromptEnergy( prompt_energy );
  model.setPromptEnergyThreshold( propmt_energy_threshold );
 }
 else
  model.setPromptVisible( false );

 DPDataCreator data_creator;

 ToolsForGATE::GlobalActorReader gar;

 model.setCreator( &data_creator );
 data_creator.setReader( &gar );

 gar.execute( input_file_name, &model, &data_creator );
 model.saveResultsToFile();

 TFile* file = ToolsForROOT::ReadAndSave::createFile( root_file_name, true );
 model.saveHistograms( file );
 ToolsForROOT::ReadAndSave::closeFile( file );
}
