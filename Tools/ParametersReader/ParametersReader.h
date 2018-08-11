#ifndef ParametersReader_h
#define ParametersReader_h

#include <string>
#include <map>
#include <utility>

namespace Tools
{
 /** @About: Simple configuration file parser
  * @Author: Mateusz Bała
  * @Email: bala.mateusz@gmail.com
 **/
 class ParametersReader
 {
  public:
   ParametersReader( std::string separator = "=", std::string file_format = ".txt" );
   ~ParametersReader();

   void extractParameters( int argc, char *argv[], int start_read_from );

   bool isParam( std::string param_key );
   double getDouble( std::string param_key );
   bool getBool( std::string param_key );
   int getInt( std::string param_key );
   std::string getString( std::string param_key );
   std::pair<double, double> getDoublePair( std::string param_key );

   void displayAllParams();

  private:
   void readFromFile( std::string file_name );
   void addNextParam( std::string line );
  private:
   std::map< std::string, std::string > fParamsMap;
   std::string fSeparator;
   std::string fFileFormat;
 };

};

#endif
