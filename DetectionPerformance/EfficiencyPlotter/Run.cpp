#include "PlotEfficiency.h"
#include "../../Tools/ToolsForROOT/ReadAndSave.h"
#include "TFile.h"

int main( int argc, char* argv[] )
{
 if ( argc < 3 )
  return 1;

 std::string input_file_name( argv[ 1 ] );
 std::string output_file_name( argv[ 2 ] );

 PlotEfficiency pe;
 if( !pe.loadFromFile( input_file_name ) )
  return 2;

 pe.showValuesForModel();

 TFile* f = ToolsForROOT::ReadAndSave::createFile( output_file_name, true );

 pe.setOutputFile( f );
 pe.saveNonPromptModelsResults();
 pe.savePromptModelsResults();

 ToolsForROOT::ReadAndSave::closeFile( f );
 //delete f;
 
 return 0;
}
