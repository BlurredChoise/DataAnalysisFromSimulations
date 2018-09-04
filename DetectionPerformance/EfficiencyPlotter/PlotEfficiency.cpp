#include "PlotEfficiency.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "../../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../../Tools/ToolsForROOT/ReadAndSave.h"

PlotEfficiency::PlotEfficiency() {}

PlotEfficiency::~PlotEfficiency() {}

bool PlotEfficiency::loadFromFile( std::string input_file_name )
{
 std::fstream f( input_file_name.c_str(), std::ios::in );
 if ( !f.good() )
  return false;
 
 std::string model_name;
 unsigned int geometry;
 double energy_threshold, energy_threshold_prompt, det, all, value;

 while ( f >> model_name >> geometry >> energy_threshold >> energy_threshold_prompt >> det >> all >> value )
  addModelValue( model_name, energy_threshold, energy_threshold_prompt, value );

 f.close();
 return true;
}

void PlotEfficiency::showValuesForModel()
{
 for ( std::map< std::string, std::vector<PlotEfficiency::PlotValue> >::iterator mit = fModels.begin(); mit != fModels.end(); ++mit )
 {
  std::cout << "MODEL: " << mit->first << std::endl;
  for ( std::vector<PlotEfficiency::PlotValue>::iterator vit = mit->second.begin(); vit != mit->second.end(); ++vit )
   std::cout << vit->energy_threshold << " " << vit->energy_threshold_prompt << " " << vit->withPrompt << " " << vit->value << std::endl;
 }
}

void PlotEfficiency::addModelValue( std::string model_name, double energy_threshold, double energy_threshold_prompt, double value )
{
 PlotEfficiency::PlotValue plot_value;
 plot_value.energy_threshold = energy_threshold;
 plot_value.energy_threshold_prompt = energy_threshold_prompt;
 plot_value.withPrompt = isPrompt( model_name );
 plot_value.value = value;

 std::map< std::string, std::vector<PlotValue> >::iterator found = fModels.find( model_name );
 if ( found == fModels.end() )
  fModels.emplace( model_name, std::vector<PlotValue>() );

 fModels[ model_name ].push_back( plot_value );
}

bool PlotEfficiency::isPrompt( std::string model_name ) { return model_name.find( "Prompt" ) != std::string::npos; }

void PlotEfficiency::saveNonPromptModelsResults()
{
 if ( fFile == nullptr )
  return;

 TH1F* h = nullptr;

 for ( std::map< std::string, std::vector<PlotEfficiency::PlotValue> >::iterator mit = fModels.begin(); mit != fModels.end(); ++mit )
  if( !isPrompt( mit->first ) && createHistogramWithoutPrompt( mit->first, mit->second, &h ) )
   ToolsForROOT::ReadAndSave::saveToFile( fFile, h );
}

bool PlotEfficiency::createHistogramWithoutPrompt( std::string model_name, std::vector<PlotValue>& data, TH1F** h )
{
 ( *h ) = nullptr;

 std::string h_name = "h_" + model_name;
 ( *h ) = ToolsForROOT::HistogramsCreator::getTH1F( h_name, 11, -5 , 105, "E_{thr} [keV]", "Efficiency [%]" );

 if ( !( *h ) )
  return false;

 for ( std::vector<PlotValue>::iterator it = data.begin(); it != data.end(); ++it )
  ( *h )->Fill( it->energy_threshold, it->value );

 return true;
}

void PlotEfficiency::savePromptModelsResults()
{
 if ( fFile == nullptr )
  return;

 std::map<double, TH1F*> hv;

 for ( std::map< std::string, std::vector<PlotEfficiency::PlotValue> >::iterator mit = fModels.begin(); mit != fModels.end(); ++mit )
  if( isPrompt( mit->first ) && createHistogramWithPrompt( mit->first, mit->second, hv ) )
  {
   for( std::map<double, TH1F*>::iterator hvit = hv.begin(); hvit != hv.end(); ++hvit )
    ToolsForROOT::ReadAndSave::saveToFile( fFile, hvit->second );
   hv.clear();
  }
}

bool PlotEfficiency::createHistogramWithPrompt( std::string model_name, std::vector<PlotValue>& data, std::map<double, TH1F*>& hv )
{
 std::string h_name;
 h_name = "h_" + model_name + "_0_keV";
 hv.emplace( 0.0, ToolsForROOT::HistogramsCreator::getTH1F( h_name, 11, -5 , 105, "E_{thr} [keV]", "Efficiency [%]" ) );

 for ( double e_thr_prompt = 360.0; e_thr_prompt <= 660.0; e_thr_prompt += 100.0 )
 {
  h_name = "h_" + model_name + "_" + std::to_string( e_thr_prompt ) + "_keV";
  hv.emplace( e_thr_prompt, ToolsForROOT::HistogramsCreator::getTH1F( h_name, 11, -5 , 105, "E_{thr} [keV]", "Efficiency [%]" ) );
 }
 
 for ( std::vector<PlotValue>::iterator it = data.begin(); it != data.end(); ++it )
 {
  std::map<double, TH1F*>::iterator hvit = hv.find( it->energy_threshold_prompt );
  if ( hvit != hv.end() )
   hv[ it->energy_threshold_prompt ]->Fill( it->energy_threshold, it->value );
 }
 return true;
}

void PlotEfficiency::setOutputFile( TFile* file ) { fFile = file; }






















