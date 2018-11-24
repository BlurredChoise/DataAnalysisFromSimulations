#include <iostream>
#include "Filter.h"
#include "TH1F.h"
#include "TH2F.h"
#include <JPetOptionsTools/JPetOptionsTools.h>
using namespace jpet_options_tools;

Filter::Filter( JPetStatistics& stats, JPetParams& params )
{
 fFiltersStatistics = &stats;
 fFiltersParameters = &params;
}

Filter::~Filter()
{
}

void Filter::add1DHist( std::string histogram_name_and_title, int bins_number, double min_value, double max_value, std::string axis_x_name, std::string axis_y_name )
{
 fFiltersStatistics->createHistogram( new TH1F(  histogram_name_and_title.c_str(),  histogram_name_and_title.c_str(), bins_number, min_value, max_value ) );
 fFiltersStatistics->getHisto1D( histogram_name_and_title.c_str() )->GetXaxis()->SetTitle( axis_x_name.c_str() );
 fFiltersStatistics->getHisto1D( histogram_name_and_title.c_str() )->GetYaxis()->SetTitle( axis_y_name.c_str() );
}

void Filter::fill1DHist( std::string histogram_name, double& value )
{
 fFiltersStatistics->getHisto1D( histogram_name.c_str() )->Fill( value );
}

void Filter::add2DHist( std::string histogram_name_and_title, int bins_number, double min_value, double max_value, std::string axis_x_name, std::string axis_y_name )
{
 fFiltersStatistics->createHistogram( new TH2F(  histogram_name_and_title.c_str(),  histogram_name_and_title.c_str(), bins_number, min_value, max_value, bins_number, min_value, max_value ) );
 fFiltersStatistics->getHisto2D( histogram_name_and_title.c_str() )->GetXaxis()->SetTitle( axis_x_name.c_str() );
 fFiltersStatistics->getHisto2D( histogram_name_and_title.c_str() )->GetYaxis()->SetTitle( axis_y_name.c_str() );
}

void Filter::fill2DHist( std::string histogram_name, double& value_x, double& value_y )
{
 fFiltersStatistics->getHisto2D( histogram_name.c_str() )->Fill( value_x, value_y );
}

bool Filter::fillDoubleParameter( std::string parameter_key, double& param_value )
{
 if ( isOptionSet( fFiltersParameters->getOptions(), parameter_key ) )
 {
  param_value = getOptionAsFloat( fFiltersParameters->getOptions(), parameter_key );
  return true;
 }
 return false;
}

bool Filter::fillIntParameter(  std::string parameter_key, int& param_value )
{
 //std::cout<<"fillIntParameter( "<< parameter_key <<", "<<param_value<<" )"<<std::endl;
 if ( isOptionSet( fFiltersParameters->getOptions(), parameter_key ) )
 {
  param_value = getOptionAsInt( fFiltersParameters->getOptions(), parameter_key );
  //std::cout<<" getOptionAsInt( fFiltersParameters->getOptions(), parameter_key ) = "<<param_value<<std::endl;
  return true;
 }
 return false; 
}

bool Filter::fillUnsignedIntParameter(  std::string parameter_key, unsigned int& param_value )
{
 //std::cout<<"fillUnsignedIntParameter( "<< parameter_key <<", "<<param_value<<" )"<<std::endl;
 if ( isOptionSet( fFiltersParameters->getOptions(), parameter_key ) )
 {
  param_value = static_cast<unsigned int>( getOptionAsInt( fFiltersParameters->getOptions(), parameter_key ) );
  //std::cout<<" getOptionAsInt( fFiltersParameters->getOptions(), parameter_key ) = "<<param_value<<std::endl;
  return true;
 }
 return false; 
}

int Filter::getIndex() const
{
 return fIndex;
}

bool Filter::setIndexForFilter( std::string parameter_key )
{
 return fillIntParameter( parameter_key, fIndex );
}

void Filter::noticeFor1DHists( std::string histogram_name_before, std::string histogram_name_after,  bool passed , double value)
{
  fill1DHist( histogram_name_before, value );
  if ( passed )
   fill1DHist( histogram_name_after, value );
}

void Filter::noticeFor2DHists( std::string histogram_name_before, std::string histogram_name_after,  bool passed , double value_x, double value_y)
{
  fill2DHist( histogram_name_before, value_x, value_y );
  if ( passed )
   fill2DHist( histogram_name_after, value_x, value_y );
}

void Filter::add1DHists( std::string histogram_name_and_title_before, std::string histogram_name_and_title_after, int bins_number, double min_value, double max_value, std::string axis_x_name, std::string axis_y_name )
{
  add1DHist( histogram_name_and_title_before, bins_number, min_value, max_value , axis_x_name, axis_y_name );
  add1DHist( histogram_name_and_title_after, bins_number, min_value, max_value , axis_x_name, axis_y_name );
}

void Filter::add2DHists( std::string histogram_name_and_title_before, std::string histogram_name_and_title_after, int bins_number, double min_value, double max_value, std::string axis_x_name, std::string axis_y_name )
{
  add2DHist( histogram_name_and_title_before, bins_number, min_value, max_value , axis_x_name, axis_y_name );
  add2DHist( histogram_name_and_title_after, bins_number, min_value, max_value , axis_x_name, axis_y_name );
}

void Filter::setName( std::string filter_name ) { fName = filter_name; }

std::string Filter::getName() { return fName; }

void Filter::add2DHists( std::string histogram_name_and_title_before, std::string histogram_name_and_title_after, int bins_number_x, double min_value_x, double max_value_x, int bins_number_y, double min_value_y, double max_value_y, std::string axis_x_name, std::string axis_y_name )
{
 fFiltersStatistics->createHistogram( new TH2F(  histogram_name_and_title_before.c_str(),  histogram_name_and_title_before.c_str(), bins_number_x, min_value_x, max_value_x, bins_number_y, min_value_y, max_value_y ) );
 fFiltersStatistics->getHisto2D( histogram_name_and_title_before.c_str() )->GetXaxis()->SetTitle( axis_x_name.c_str() );
 fFiltersStatistics->getHisto2D( histogram_name_and_title_before.c_str() )->GetYaxis()->SetTitle( axis_y_name.c_str() );

 fFiltersStatistics->createHistogram( new TH2F(  histogram_name_and_title_after.c_str(),  histogram_name_and_title_after.c_str(), bins_number_x, min_value_x, max_value_x, bins_number_y, min_value_y, max_value_y ) );
 fFiltersStatistics->getHisto2D( histogram_name_and_title_after.c_str() )->GetXaxis()->SetTitle( axis_x_name.c_str() );
 fFiltersStatistics->getHisto2D( histogram_name_and_title_after.c_str() )->GetYaxis()->SetTitle( axis_y_name.c_str() );
}

void Filter::coutLine() { std::cout << " --------------------------------------------------- " << std::endl; }

bool Filter::getBoolParamValue( std::string param_key )
{
return isOptionSet( fFiltersParameters->getOptions(), param_key ) && getOptionAsBool( fFiltersParameters->getOptions(), param_key );
}
