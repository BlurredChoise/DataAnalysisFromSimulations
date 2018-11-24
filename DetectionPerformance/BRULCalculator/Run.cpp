#include "BRUL.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TMath.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include "TH1F.h"
#include <vector>
#include "TLegend.h"
#include "TROOT.h"
#include "TStyle.h"

// tmin tmax sigma image_name E_thr eff [ E_thr eff ] ...
int main( int argc, char* argv[] )
{
 double aCL = 2.44;
 const double source_activity = 10;//MBq
 const unsigned int Nbg = 1;

 if ( argc < 5 || ( argc % 2 != 1 ) ) { std::cerr << "Incorrect number of parameters" << std::endl; return 1; }

 bool use_eta = atoi( argv[ 1 ] ) == 1;
 std::cout<< "use_eta " << use_eta << std::endl;
 double prompt_eff = atof( argv[ 2 ] ) / 100.0;
 double t_min_days = atof( argv[ 3 ] );
 double t_max_days = atof( argv[ 4 ] );
 double sigma = atof( argv[ 5 ] );
 std::string image_name = std::string( argv[ 6 ] );
 

 double Ethr = 0.0, eff = 0.0;
 std::string fun_name = "";

 if( use_eta ) { aCL = 1.0; }

 std::vector< BRUL > brs;

 for ( int i = 7; i < argc; i += 2 )
 {
  Ethr = atof( argv[ i ] );
  eff = atof( argv[ i +1 ] ) / 100.0;
  if( use_eta ) { eff *= prompt_eff; }
  BRUL br;
  br.setBRParameterFromCL( aCL );
  br.setNBackground( Nbg );
  br.setEfficiency( eff );
  br.setSigma( sigma );
  br.setTimeRange( t_min_days, t_max_days );
  br.setSourceActivity( source_activity );
  fun_name = "E_{thr} = " + std::to_string( static_cast<unsigned int>( Ethr ) ) + " keV";
  br.setFunctionName( fun_name );
  brs.push_back( br );
 }

 std::string axis_x_name = "Measurement time [days]";
 std::string axis_y_name = use_eta ? "#eta" : "BR^{upper}_{limit}(CL=90%)";

 unsigned int size = brs.size();

 TCanvas c("c");

 TF1* fun = nullptr;

 auto legend = new TLegend(0.5,0.7,0.9,0.9);
 legend->SetHeader("Used energy threshold","C"); // option "C" allows to center the header

 double y_max = 0, y_min = 1000000;

 for ( unsigned int i = 0; i < size; ++i )
 {
  fun = brs[ i ].getBRULFunction();
  y_max = TMath::Max( y_max, fun->Eval( t_min_days ) );
  y_min = TMath::Min( y_min, fun->Eval( t_max_days ) );
 }

 std::cout << y_min << " " << y_max << std::endl;

  const double fFontSize = 0.049;
  const double fTitleOffset = 0.88;

 auto generatorBRULX = [ = ]( double * args, double * params )->double{ 
  if ( args[ 0 ] < t_min_days * 1.1 ) 
   return y_max;
  return y_min;
 };

 TH1F h0( "h", "h", 10, t_min_days, t_max_days );
 h0.SetTitle( "" );
 h0.SetStats(0);
 h0.SetLineColor(0);
 h0.GetXaxis()->SetTitleSize( fFontSize );
 h0.GetYaxis()->SetTitleSize( fFontSize );
 h0.GetXaxis()->SetTitleOffset( fTitleOffset );
 h0.GetYaxis()->SetTitleOffset( fTitleOffset );
 h0.GetXaxis()->SetTitle( axis_x_name.c_str() );
 h0.GetYaxis()->SetTitle( axis_y_name.c_str() );
 h0.Fill( t_max_days-100, y_max );
 h0.Fill( t_max_days-10, y_min );

 h0.Draw("hist");

 /*TF1 f0( "f0", generatorBRULX , t_min_days, t_max_days, 0 );
 f0.SetLineColor( 0 );
 f0.SetTitle("");
 gStyle->SetTitleFontSize( fFontSize );
 f0.GetHistogram()->GetXaxis()->SetTitleSize( fFontSize );
 f0.GetHistogram()->GetYaxis()->SetTitleSize( fFontSize );
 f0.GetHistogram()->GetXaxis()->SetTitleOffset( fTitleOffset );
 f0.GetHistogram()->GetYaxis()->SetTitleOffset( fTitleOffset );
 f0.GetHistogram()->GetXaxis()->SetTitle( axis_x_name.c_str() );
 f0.GetHistogram()->GetYaxis()->SetTitle( axis_y_name.c_str() );
 f0.Draw("same");*/

 for ( unsigned int i = 0; i < size; ++i )
 {
  fun = brs[ i ].getBRULFunction();
  fun->SetLineColor( i + 1 );
  legend->AddEntry( fun, fun->GetTitle(), "l" );
  fun->SetTitle( "" );


  fun->Draw( "same" );
 }

 legend->Draw( "same" );
 gPad->SetLogx( 1 );
 gPad->SetLogy( 1 );
 c.Print( image_name.c_str() );

 return 0;
}
