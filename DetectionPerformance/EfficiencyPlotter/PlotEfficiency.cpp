#include "PlotEfficiency.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "../../Tools/ToolsForROOT/HistogramsCreator.h"
#include "../../Tools/ToolsForROOT/ReadAndSave.h"
#include "TLine.h"

PlotEfficiency::PlotEfficiency() {c = new TCanvas("c"/*, "c", 2000, 1500 */);}

PlotEfficiency::~PlotEfficiency() { delete c; }

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
 ( *h ) = ToolsForROOT::HistogramsCreator::getTH1F( h_name, 11, -5 , 105, "E_{thr} [keV]", "Efficiency" );

 if ( !( *h ) )
  return false;

 ( *h )->SetTitle( "" );
 ( *h )->SetStats();

 double max_value = 0, min_value = 10000;
 double y_line = 0, y_line_min = 0;

 for ( std::vector<PlotValue>::iterator it = data.begin(); it != data.end(); ++it )
 {
  max_value = TMath::Max( max_value, it->value/100.0 );
  min_value = TMath::Min( min_value, it->value/100.0 );
  ( *h )->Fill( it->energy_threshold, it->value/100.0 );
 }

 double v = 0, v2 = 0;
 bool b1 = false, b2 = false;
 for ( double d = 100; d >= 0.00000000001; d  = d / 10.0 )
 {
  if ( b1 && b2 )
   break;

  v = max_value / d;
  v2 = min_value / d;

  if ( !b1 && v < 10.0 && v > 1.0 )
  {
   y_line = d * 10.0;
   b1 = true;
  }
  
  if ( !b2 & v2 < 10.0 && v2 > 1.0 )
  {
   y_line_min = d;
   b2 = true;
  }
 }

 TH1F* h0 = ToolsForROOT::HistogramsCreator::getTH1F( "testing", 11, -5 , 105, "E_{thr} [keV]", "Efficiency" );
 h0->Fill( 0.0,  y_line );
 std::cout << "y_line_min " << y_line_min << std::endl;
 h0->Fill( 100.0,  y_line_min );
 h0->SetLineColor(0);
 h0->SetTitle( "" );
 h0->SetStats(0);
 h0->GetXaxis()->SetTitleSize( fFontSize );
 h0->GetYaxis()->SetTitleSize( fFontSize );
 h0->GetYaxis()->SetMaxDigits( fDigits );
 h0->GetXaxis()->SetTitleOffset( fTitleOffset );
 h0->GetYaxis()->SetTitleOffset( fTitleOffset );
 /*h0->GetXaxis()->SetLabelSize( fFontSize ); 
 h0->GetYaxis()->SetLabelSize( fFontSize );*/
 h0->Draw("hist C" );

 std::string img_name = h_name + ".png";
 ( *h )->SetTitle( "" );
 ( *h )->SetStats(0);
 ( *h )->GetXaxis()->SetTitleSize( fFontSize );
 ( *h )->GetYaxis()->SetTitleSize( fFontSize );
 ( *h )->GetYaxis()->SetMaxDigits( fDigits );
 //( *h )->Smooth();
 ( *h )->Draw("same *hist C" );
 //line.Draw("same");
 gPad->SetLogy( 1 );
 c->Print( img_name.c_str() );

 delete h0;
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

void getDV( double& y1, double& d1, double& y2, double& d2 )
{
 double v = 0, v2 = 0;
 bool b1 = false, b2 = false;
 for ( double d = 100; d >= 0.00000000001; d  = d / 10.0 )
 {
  if ( b1 && b2 )
   break;

  v = y1 / d;
  v2 = y2 / d;

  if ( !b1 && v < 10.0 && v > 1.0 )
  {
   d1 = d * 10.0;
   b1 = true;
  }
  
  if ( !b2 & v2 < 10.0 && v2 > 1.0 )
  {
   d2 = d;
   b2 = true;
  }
 }

}

bool PlotEfficiency::createHistogramWithPrompt( std::string model_name, std::vector<PlotValue>& data, std::map<double, TH1F*>& hv )
{
 std::string h_name;
 h_name = "h_" + model_name + "_0_keV";
 hv.emplace( 0.0, ToolsForROOT::HistogramsCreator::getTH1F( h_name, 11, -5 , 105, "E_{thr} [keV]", "Efficiency" ) );
  hv[ 0.0 ]->SetTitle("");
  hv[ 0.0 ]->SetStats(0);
  hv[ 0.0 ]->GetXaxis()->SetTitleSize( fFontSize );
  hv[ 0.0 ]->GetYaxis()->SetTitleSize( fFontSize );
  hv[ 0.0 ]->GetYaxis()->SetMaxDigits( fDigits );


 for ( double e_thr_prompt = 360.0; e_thr_prompt <= 660.0; e_thr_prompt += 100.0 )
 {
  h_name = "h_" + model_name + "_" + std::to_string( e_thr_prompt ) + "_keV";
  hv.emplace( e_thr_prompt, ToolsForROOT::HistogramsCreator::getTH1F( h_name, 11, -5 , 105, "E_{thr} [keV]", "Efficiency" ) );
  hv[ e_thr_prompt ]->GetXaxis()->SetTitleSize( fFontSize );
  hv[ e_thr_prompt ]->GetYaxis()->SetTitleSize( fFontSize );
  hv[ e_thr_prompt ]->SetTitle("");
  hv[ e_thr_prompt ]->SetStats(0);
  hv[ e_thr_prompt ]->GetYaxis()->SetMaxDigits( fDigits );
 }
 
 for ( std::vector<PlotValue>::iterator it = data.begin(); it != data.end(); ++it )
 {
  std::map<double, TH1F*>::iterator hvit = hv.find( it->energy_threshold_prompt );
  if ( hvit != hv.end() )
   hv[ it->energy_threshold_prompt ]->Fill( it->energy_threshold, it->value/100.0 );
 }

 std::string img_name;

 for ( std::map<double, TH1F*>::iterator it = hv.begin(); it != hv.end(); ++it )
 {
  double y1 = it->second->GetBinContent(1);
  double y2 = it->second->GetBinContent(11);
  std::cout<< "y1 = " << y1 << "y2 = " << y2 << std::endl;
  double d1 = 0, d2 = 0;
  getDV( y1, d1, y2, d2 );
  
 TH1F* h0 = ToolsForROOT::HistogramsCreator::getTH1F( "testing", 11, -5 , 105, "E_{thr} [keV]", "Efficiency" );
 h0->Fill( 0.0,  d1 );
 h0->Fill( 100.0,  d2 );
 h0->SetLineColor(0);
 h0->SetTitle( "" );
 h0->SetStats(0);
 h0->GetXaxis()->SetTitleSize( fFontSize );
 h0->GetYaxis()->SetTitleSize( fFontSize );
 h0->GetYaxis()->SetMaxDigits( fDigits );
 h0->GetXaxis()->SetTitleOffset( fTitleOffset );
 h0->GetYaxis()->SetTitleOffset( fTitleOffset );
 h0->Draw("hist C" );

  img_name = std::string( it->second->GetName() ) + ".png";
  //it->second->Smooth();
  it->second->Draw("same *hist C");
  gPad->SetLogy( 1 );
  c->Print(img_name.c_str());
  delete h0;
 } 

 return true;
}

void PlotEfficiency::setOutputFile( TFile* file ) { fFile = file; }






















