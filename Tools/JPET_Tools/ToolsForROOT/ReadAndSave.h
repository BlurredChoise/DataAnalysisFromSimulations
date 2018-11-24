#ifndef ReadAndSave_h
#define ReadAndSave_h
#include "TH1F.h"
#include "TFile.h"
#include <string>
#include "TF1.h"
#include "TGraph.h"
#include "TH2F.h"
#include "TH1I.h"
#include "TVector3.h"
#include "TObject.h"
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This is simple static class which provides simple methods for saving to and reading from ROOT file. Methods in this class take care of exception like not existng file, objects, etc. Use this methods to reduce size of your code.
*/
namespace ToolsForROOT
{
 class ReadAndSave
 {
  public:

   static void saveToFile( TFile* file, TObject* object );

   static TH1F* getHistogram1DFromFile( TFile* file, std::string histogram_name );

   static TH2F* getHistogram2DFromFile( TFile* file, std::string histogram_name );

   static TGraph* getGraphFromFile( TFile* file, std::string graph_name );

   static TF1* getFunctionFromFile( TFile* file, std::string function_name );

   static TFile* openFileForRead(std::string file_name);

   static TFile* createFile(std::string file_name, bool overwrite_if_exists);

   static void closeFile(TFile* file);
 };
};

#endif

