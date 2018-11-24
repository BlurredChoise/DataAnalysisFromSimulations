#ifndef PlotEfficiency_h
#define PlotEfficiency_h

#include<map>
#include<vector>
#include<string>
#include "TH1F.h"
#include "TFile.h"
#include "TCanvas.h"

class PlotEfficiency
{
 public:
  struct PlotValue
  {
   double energy_threshold;
   double energy_threshold_prompt;
   bool withPrompt;
   double value;
  };

 public:
  PlotEfficiency();
  ~PlotEfficiency();

  bool loadFromFile( std::string input_file_name );
  void showValuesForModel();

  void saveNonPromptModelsResults();
  void savePromptModelsResults();
  void setOutputFile( TFile* file );

 private:
  void addModelValue( std::string model_name, double energy_threshold, double energy_threshold_prompt, double value );
  bool isPrompt( std::string model_name );
  bool createHistogramWithoutPrompt( std::string model_name, std::vector<PlotValue>& data, TH1F** h );
  bool createHistogramWithPrompt( std::string model_name, std::vector<PlotValue>& data, std::map<double, TH1F*>& hv );

 private:
  std::map< std::string, std::vector<PlotValue> > fModels;//<model_name, values >
  TFile* fFile = nullptr;
  TCanvas* c = nullptr;
  const double fFontSize = 0.049;
  const int fDigits = 2;
  const double fTitleOffset = 0.78;
};

#endif
