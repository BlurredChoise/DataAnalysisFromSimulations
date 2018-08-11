#include "ReadAndSave.h"
#include "Message.h"
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This is simple static class which provides simple methods for saving to and reading from ROOT file. Methods in this class take care of exception like not existng file, objects, etc. Use this methods to reduce size of your code.
*/

namespace ToolsForROOT
{

 void ReadAndSave::saveToFile( TFile* file, TObject* object )
 {
  if ( Message::error( file != 0 && file->IsOpen(), "File not found") )
   return;
  if ( Message::error( object, "Null object - nothing to save" ) )
  file->cd();
  object->Write( object->GetName() );
 }

 TH1F* ReadAndSave::getHistogram1DFromFile( TFile* file, std::string histogram_name )
 {
  if ( Message::error( file != 0 && file->IsOpen(), "File not found. Cannot extract histogram : " + histogram_name ) )
   return 0;
  TH1F* ptr_histogram = dynamic_cast< TH1F* >( file->Get( histogram_name.c_str() ) );
  Message::error( ptr_histogram != 0, "Histogram \"" + histogram_name + "\" not found" );
  return ptr_histogram; 
 }

 TH2F* ReadAndSave::getHistogram2DFromFile( TFile* file, std::string histogram_name )
 {
  if ( Message::error( file != 0 && file->IsOpen(), "File not found. Cannot extract histogram : " + histogram_name ) )
   return 0;
  TH2F* ptr_histogram = dynamic_cast< TH2F* >( file->Get( histogram_name.c_str() ) );
  Message::error( ptr_histogram != 0, "Histogram \"" + histogram_name + "\" not found" );
  return ptr_histogram; 
 }

 TGraph* ReadAndSave::getGraphFromFile( TFile* file, std::string graph_name )
 {
  if ( Message::error( file != 0 && file->IsOpen(), "File not found. Cannot extract graph : " + graph_name ) )
   return 0;
  TGraph* ptr_graph = dynamic_cast< TGraph* >( file->Get( graph_name.c_str() ) );
  Message::error( ptr_graph != 0, "Graph \"" + graph_name + "\" not found" );
  return ptr_graph; 
 }

 TF1* ReadAndSave::getFunctionFromFile( TFile* file, std::string function_name )
 {
  if ( Message::error( file != 0 && file->IsOpen(), "File not found. Cannot extract function : " + function_name ) )
   return 0;
  TF1* ptr_function = dynamic_cast< TF1* >( file->Get( function_name.c_str() ) );
  Message::error( ptr_function != 0, "Graph \"" + function_name + "\" not found" );
  return ptr_function; 
 }

 TFile* ReadAndSave::openFileForRead(std::string file_name)
 {
  TFile* file = new TFile(file_name.c_str(),"READ");
  Message::error( file != 0, "File \"" + file_name + "\" not found." );
  return file;
 }

 TFile* ReadAndSave::createFile(std::string file_name, bool overwrite_if_exists)
 {
  TFile* file = 0;
  if ( overwrite_if_exists )
   file = new TFile( file_name.c_str(), "RECREATE" );
  else
   file = new TFile( file_name.c_str(), "CREATE" );

  Message::error( file != 0, "File cannot be created. File name: " + file_name );
  
  return file;
 }

 void ReadAndSave::closeFile( TFile* file )
 {
  if ( Message::error( file != 0 && file->IsOpen(), "File not found. Can not close not existing file." ) )
   return;  
  file->Close( "R" );
 }

};
