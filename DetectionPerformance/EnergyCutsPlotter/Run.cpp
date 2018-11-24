#include<iostream>
#include<string>
#include<cstdlib>
#include "TH1F.h"
#include "TLine.h"
#include "TFile.h"
#include "TCanvas.h"
#include "../../Tools/ToolsForROOT/ReadAndSave.h"

/*void DrawCutsForNonPrompt( double y2 )
{
 TLine line_50( 50, 0, 50, y2 );
 TLine line_70( 70, 0, 70, y2 );
 TLine line_100( 100, 0, 100, y2 );
 
 line_50.SetLineColor(2);
 line_70.SetLineColor(6);
 line_100.SetLineColor(1);

 line_50.Draw("same");
 line_70.Draw("same");
 line_100.Draw("same");
}

void DrawCutsForPrompt( double y2 )
{
 TLine line_460( 460, 0, 460, y2 );
 line_460.SetLineColor(3);
 line_460.Draw("same");
}*/

void DrawHistogram( TH1F& h0, unsigned int rebin, double xmax, std::string image_name, bool use_prompt_cut, unsigned int cutno )
{
 std::cout<< "h0.GetBinWidth(0) h0.GetBinWidth(1) " << h0.GetBinWidth(0) <<" " << h0.GetBinWidth(1) << std::endl;

 TCanvas c("c");
 TH1F h = h0;
 h.SetTitle("");
 h.SetStats(0);
 h.GetXaxis()->SetTitle("#Delta E_{dep} [keV]" );

  const double fFontSize = 0.049;
  const int fDigits = 2;
  const double fTitleOffset = 0.78;

 h.GetXaxis()->SetTitleSize( fFontSize );
 h.GetYaxis()->SetTitleSize( fFontSize );
 h.GetYaxis()->SetMaxDigits( fDigits );
 h.GetXaxis()->SetTitleOffset( fTitleOffset );
 h.GetYaxis()->SetTitleOffset( fTitleOffset );

 h.Rebin( rebin );
 std::cout<< "h.GetBinWidth(0) h.GetBinWidth(1) " << h.GetBinWidth(0) <<" " << h.GetBinWidth(1) << std::endl;
 std::cout<< "GetMaximum " << h.GetYaxis()->GetBinCenter( h.GetYaxis()->GetLast() ) << " " <<h.GetMaximum() << std::endl;
 double y2 = h.GetMaximum() * 1.1;
 h.GetXaxis()->SetRangeUser( 0, xmax );
 h.GetYaxis()->SetRangeUser( 0, y2 );
 h.Draw("hist");

 TLine line_50( 50, 0, 50, y2 );
 TLine line_70( 70, 0, 70, y2 );
 TLine line_100( 100, 0, 100, y2 );
 
 line_50.SetLineColor(2);
 line_70.SetLineColor(6);
 line_100.SetLineColor(1);

 TLine line_460( 460, 0, 460, y2 );
 line_460.SetLineColor(3);

 if ( cutno == 0 || cutno == 50 )
  line_50.Draw("same");
 if ( cutno == 0 || cutno == 70 )
  line_70.Draw("same");
 if ( cutno == 0 || cutno == 100 )
  line_100.Draw("same");

 if ( use_prompt_cut )
  line_460.Draw("same");

 c.Print( image_name.c_str() );
}

int main( int argc, char* argv[] )
{
 if ( argc != 8 )
  return 1;

 std::string input_file_name( argv[ 1 ] );
 std::string image_name( argv[ 2 ] );
 unsigned int rebin = static_cast<unsigned int>( atoi( argv[ 3 ] ) );
 double xmax = atof( argv[ 4 ] );
 bool use_prompt_cut = atoi( argv[ 5 ] ) == 1;
 unsigned int option = static_cast<unsigned int>( atoi( argv[ 6 ] ) );
 unsigned int cutno = static_cast<unsigned int>( atoi( argv[ 7 ] ) );

 TFile* f = ToolsForROOT::ReadAndSave::openFileForRead(input_file_name);
 TH1F* h = nullptr;

 switch( option )
 {
  case 0:
   h = dynamic_cast<TH1F*>( f->Get("h1EnergyDepositionAcceptedBeforeCuts") );
   break;
  case 1:
   h = dynamic_cast<TH1F*>( f->Get("h1EnergyDepositionAcceptedBeforeCutsFirstScattering") );
   break;
  case 2:
   h = dynamic_cast<TH1F*>( f->Get("h1EnergyDepositionAcceptedBeforeCutsSecondScattering") );
   break;
 };

 if ( h == nullptr )
  return 2;

 DrawHistogram( *h, rebin, xmax, image_name, use_prompt_cut, cutno );
 //TCanvas c("c");
 //h->Draw("hist");
 //DrawHistogram( *h, rebin, xmax );
 //DrawCutsForNonPrompt( y2 );
 //DrawCutsForNonPrompt( y2 );

 //c.Print( image_name.c_str() );
 ToolsForROOT::ReadAndSave::closeFile( f );
}
