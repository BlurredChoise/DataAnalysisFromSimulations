#include <iostream>
#include <locale>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include "ParametersReader.h"

namespace Tools
{
 ParametersReader::ParametersReader( std::string separator, std::string file_format ) 
 {
  fSeparator = separator;
  fFileFormat = file_format;
 }

 ParametersReader::~ParametersReader() {}

 void ParametersReader::extractParameters( int argc, char *argv[], int start_read_from )
 {
  int index_start_from = start_read_from;
  std::string str_to_check( argv[ start_read_from ] );
  size_t found = str_to_check.find( fFileFormat );
  if ( found != std::string::npos )
  {
   ++index_start_from;
   readFromFile( str_to_check );
  }

  for ( int index = index_start_from; index < argc; ++index )
   addNextParam( std::string( argv[ index ] ) );
 }

 bool ParametersReader::isParam( std::string param_key ) { return fParamsMap.find( param_key ) != fParamsMap.end(); }

 double ParametersReader::getDouble( std::string param_key ) { return atof( fParamsMap.at( param_key ).c_str() ); }

 bool ParametersReader::getBool( std::string param_key ) 
 { 
  std::string param_value = fParamsMap.at( param_key );
  std::string value = "";
  std::locale loc;
  for ( std::string::size_type i = 0; i < param_value.length(); ++i )
   value += std::toupper( param_value[ i ], loc );

  if ( value == "TRUE" )
   return true;
  return false;
 }

 int ParametersReader::getInt( std::string param_key ) { return atoi( fParamsMap.at( param_key ).c_str() ); }

 std::string ParametersReader::getString( std::string param_key ) { return fParamsMap.at( param_key ); }

 std::pair<double, double> ParametersReader::getDoublePair( std::string param_key )
 {
  std::string param_value = fParamsMap.at( param_key );
  size_t pair_separator_position = param_value.find( "," );
  if ( pair_separator_position == std::string::npos )
   return std::make_pair( 0.0, 0.0 );

  std::string valueA = param_value.substr( 0, pair_separator_position );
  std::string valueB = param_value.substr( pair_separator_position + 1, param_value.size() - pair_separator_position - 1 );

  return std::make_pair( atof( valueA.c_str() ), atof( valueB.c_str() ) );
 }

 void ParametersReader::readFromFile( std::string file_name )
 {
  std::fstream file( file_name.c_str(), std::ios::in );
  std::string line;

  while( getline( file, line ) )
   addNextParam( line );  

  file.close();
 }

 void ParametersReader::addNextParam( std::string line )
 {
  size_t separator_position = line.find( fSeparator );
  if ( separator_position == std::string::npos )
   return;
  std::string param_key = line.substr( 0, separator_position );
  std::string param_value = line.substr( separator_position + 1, line.size() - separator_position - 1 );

  param_key.erase( std::remove( param_key.begin(), param_key.end(), ' ' ), param_key.end() );
  param_value.erase( std::remove( param_value.begin(), param_value.end(), ' ' ), param_value.end() );

  if ( fParamsMap.find( param_key ) == fParamsMap.end() )
   fParamsMap.emplace( param_key, param_value );
 }

 void ParametersReader::displayAllParams()
 {
  std::cout << "--------------------------------------------------" << std::endl;
  std::cout << "Loaded parameters: " << std::endl;
  for ( std::map< std::string, std::string >::iterator it = fParamsMap.begin(); it != fParamsMap.end(); ++it )
   std::cout << "|" << it->first << "|" << it->second << "|" << std::endl;
  std::cout << "--------------------------------------------------" << std::endl;
 }
 
};
