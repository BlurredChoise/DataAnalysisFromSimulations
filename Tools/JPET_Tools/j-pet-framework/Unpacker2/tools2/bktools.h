#ifndef BKTOOLS_H
#define BKTOOLS_H

#include "TMath.h"

//Gaussian ala CMSFitTutorial
Double_t GaussFitFunc2(Double_t * x, Double_t * par)
{
  Double_t arg = 0;
  if (par[2]<0) par[2]=-par[2];  // par[2]: sigma
  if (par[2] != 0) arg = (x[0] - par[1])/par[2];  // par[1]: mean
 
  //return par[0]*BIN_SIZE*TMath::Exp(-0.5*arg*arg)/
  //   (TMath::Sqrt(2*TMath::Pi())*par[2]); 
   return par[0]*TMath::Exp(-0.5*arg*arg)/
     (TMath::Sqrt(2*TMath::Pi())*par[2]); // par[0] is constant
 
}


// Gaussian ala QAPlots
Double_t GaussFitFunc(Double_t* x_val, Double_t* par)
{
    Double_t x, y, par0, par1, par2;
    par0  = par[0];
    par1  = par[1];
    par2  = par[2];
    x = x_val[0];
    y = par0*TMath::Gaus(x,par1,par2,0);
    return y;
}


// this function is setting the style of canvas
// as an argument one should give the name of canvas
// and the number of columns and rows, e.g. setOPT_canavas(canvaspointer)

// this is official size of the canvas,
// it should be setted once you are declaring it
// TCanvas *signal = new TCanvas("signal", "Pair-Signal Aug04",158,28,900,918);
void setOPT_canvas(TCanvas *canvas)
{
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);    // X errors of the data points set to be 0
    gStyle->SetLineStyleString(22,"80 18 12 18 12 12"); // special style for the line
    gStyle->SetEndErrorSize(5);   // define end width of error bars
    gStyle->SetCanvasColor(10);
    gStyle->SetPadColor(10);
    canvas->SetLeftMargin(0.11);
    canvas->SetRightMargin(0.07);
    canvas->SetTopMargin(0.04);
    canvas->SetBottomMargin(0.09);
    canvas->ToggleEventStatus();
    canvas->Range(-194.483,-10.3682,1041.38,-2.08469);
    canvas->SetFillColor(0);
    canvas->SetBorderMode(0);
    canvas->SetBorderSize(0);
    canvas->SetTickx();
    canvas->SetTicky();
//    canvas->SetLogy();
    canvas->SetFrameLineWidth(2);
    canvas->SetFrameBorderMode(0);
    canvas->SetFrameBorderSize(0);
}
// this function is setting the style of the plotting historgrams
// as an argument one should give name of the histogram, title of the X and Y axis
// Ndevision for the X axis, style, size and the color of the marker
// e.g for the official PRL plot for the RAW spectra of the NOV02 it was used in the following way:
// setOPT_hists(signal,20,1.3);
// setOPT_hists(background,24,1.3,2);
// setOPT_hists(unlikesign,22,1.3,4);
void setOPT_func(TF1 *func, Int_t marker_style =3002, Float_t marker_size =1, Int_t color=0)
{
//    func->SetFillColor(color+1011);
//    func->SetFillStyle(marker_style);
    func->SetLineWidth(marker_size);
    func->SetLineColor(color+1001);
/*
    hist->GetXaxis()->SetRangeUser(XRangeMin,XRangeMax);
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.06);
    hist->GetYaxis()->SetTitleSize(0.06);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.16);
    //hist->GetXaxis()->CenterTitle();
    //hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.05);
    hist->GetYaxis()->SetLabelSize(0.05);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color+1001);
    hist->SetTitle();
*/
}

void setOPT_hists(TH1F *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.3, Int_t color=0, Int_t XRangeMin, Int_t XRangeMax)
{
    hist->SetFillColor(color+1011);
    hist->SetFillStyle(3002);
    hist->SetLineWidth(1);
    hist->GetXaxis()->SetRangeUser(XRangeMin,XRangeMax);
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.04);
    hist->GetYaxis()->SetTitleSize(0.04);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.14);
    //hist->GetXaxis()->CenterTitle();
    //hist->GetYaxis()->CenterTitle();
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.03);
    hist->GetYaxis()->SetLabelSize(0.03);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->SetMarkerColor(color+1001);
    hist->SetLineColor(color+1001);
    hist->SetTitle();
}

void setOPT_hists(TH2F *hist, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.3, Int_t color=0, Int_t YRangeMin,Int_t YRangeMax, Int_t XRangeMin, Int_t XRangeMax)
{
    hist->GetXaxis()->SetTitle(xAxisTitle);
    hist->GetYaxis()->SetTitle(yAxisTitle);
    hist->GetXaxis()->SetTitleSize(0.04);
    hist->GetYaxis()->SetTitleSize(0.04);
    hist->GetZaxis()->SetTitleSize(0.04);
    hist->GetXaxis()->SetTitleFont(42);
    hist->GetYaxis()->SetTitleFont(42);
    hist->GetZaxis()->SetTitleFont(42);
    hist->GetXaxis()->SetNdivisions(Ndevision);
    hist->GetYaxis()->SetTitleOffset(1.14);
    hist->GetXaxis()->SetLabelFont(42);
    hist->GetYaxis()->SetLabelFont(42);
    hist->GetZaxis()->SetLabelFont(42);
    hist->GetXaxis()->SetLabelSize(0.03);
    hist->GetYaxis()->SetLabelSize(0.03);
    hist->GetZaxis()->SetLabelSize(0.02);
    hist->SetFillColor(10);
    hist->SetTitle();
    hist->SetMarkerColor(color+1001);
    hist->SetMarkerStyle(marker_style);
    hist->SetMarkerSize(marker_size);
    hist->GetYaxis()->SetRangeUser(YRangeMin,YRangeMax);
    hist->GetXaxis()->SetRangeUser(XRangeMin,XRangeMax);
}


void myLegendSetUp(TLegend *currentLegend=0,float currentTextSize=0.07){
  currentLegend->SetTextFont(42);
  currentLegend->SetBorderSize(0);
  currentLegend->SetFillStyle(0);
  currentLegend->SetFillColor(0);
  currentLegend->SetMargin(0.25);
  currentLegend->SetTextSize(currentTextSize);
  currentLegend->SetEntrySeparation(0.5);
  return;
}

void set_plot_style()
{
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
}

// Nice Colors
void set_nice_color()
{
     Float_t pred, pgreen, pblue;
     Int_t   i;


      Float_t  psaturation = 1.;
      Float_t  psaturationLow = 0.5;
      Float_t  plightness = 1.;
      Float_t  pmaxHue = 320;
      Float_t  pminHue = 0;
      Int_t    pmaxPretty = 8;
      Float_t  phue;

      for (i=0; i<pmaxPretty; i++) {
         phue = pmaxHue-(i+1)*((pmaxHue-pminHue)/pmaxPretty);
         TColor::HSV2RGB(phue, psaturation, plightness, pred, pgreen, pblue);
         new TColor(pmaxPretty-i+1000, pred, pgreen, pblue);
         TColor::HSV2RGB(phue, psaturationLow, plightness, pred, pgreen, pblue);
         new TColor(pmaxPretty-i+1010, pred, pgreen, pblue);
      }
}

void Format_hist(TH1F **hist, TString Title="", Int_t scale=1.3)
{
	Int_t MaxRange;
	for(int j = 0; j < 8; j++) {
	      if (Channels[j] == 1) { 	// if channel on
	 	 if (MaxRange < hist[j]->GetBinContent(hist[j]->GetMaximumBin())) MaxRange = hist[j]->GetBinContent(hist[j]->GetMaximumBin());
	   }	
	 }

	 MaxRange = MaxRange * scale;
cout<<"MaxRange"<<MaxRange<<endl;
	 for(int j = 0; j < 8; j++) {
	 hist[j]->SetTitle(Title);
	 hist[j]->GetYaxis()->SetRangeUser(0,MaxRange);
	 }
}



void Fit_hist(TH1F *hist, TF1 *funcFit, TString xAxisTitle=" ", TString yAxisTitle=" ", Int_t Ndevision=510, Int_t marker_style =20, Float_t marker_size =1.3, Int_t color=0, Int_t XRangeMin, Int_t XRangeMax)
{
      Int_t   i;
	 for (int i = 0; i < 8; i++) {

     if (Channels[i] == 1) {
	if(timeDiff[i]->GetEntries() > 0)
	{	
	timeDiffMean[i]=timeDiff[i]->GetMean();
	timeDiffMax[i]=timeDiff[i]->GetBinCenter(timeDiff[i]->GetMaximumBin());
	timeDiffSig[i]=timeDiff[i]->GetRMS();

            //Fitting
	    for(Int_t n=0; n<3; n++)
	    {
		funcFit->ReleaseParameter(n);
		funcFit->SetParameter(n,0.0);
	    }

		funcFit->SetParName(0,"Const");
		funcFit->SetParName(1,"Mean");
		funcFit->SetParName(2,"Sigma");

	    if(sums[i]->GetEntries()>300)
	    {
		funcFit->SetParameter(0,timeDiff[i]->GetMaximum());
		funcFit->SetParameter(1,timeDiffMax[i]);
		funcFit->SetParameter(2,timeDiffSig[i]);

//		sumsFit[i]->SetRange(sumsMax[i]-(sumsSig[i]),sumsMax[i]+(sumsSig[i]));
		timeDiff[i]->Fit(Form("timeDiffFit[%i]",i),"+Q0","",timeDiffMax[i]-(timeDiffSig[i]*3),timeDiffMax[i]+(timeDiffSig[i]*3));		
//		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q0","",sumRangeMin,sumRangeMax);
//		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q",""); //,sumsMax[i]*0.9,sumsMax[i]*1.1);
		timeDiffMean[i]=timeDiffFit[i]->GetParameter(1);
		timeDiffSig[i]=timeDiffFit[i]->GetParameter(2);

//		sumsFit[i]->SetRange(sumsMean[i]-(sumsSig[i]),sumsMean[i]+(sumsSig[i]));
		timeDiff[i]->Fit(Form("timeDiffFit[%i]",i),"+Q","",timeDiffMean[i]-(timeDiffSig[i]*3),timeDiffMean[i]+(timeDiffSig[i]*3));
//		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q","",sumsMean[i]-(sumsSig[i]/2.35),sumsMean[i]+(sumsSig[i]/2.35));
//		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q","",sumsMax[i]*0.9,sumsMax[i]*1.1);
		timeDiffMean[i]=timeDiffFit[i]->GetParameter(1);
		timeDiffSig[i]=timeDiffFit[i]->GetParameter(2);
		timeDiffChisquare[i]=timeDiffFit[i]->GetChisquare();



	    }
	}

    		timeDiffRes[i] = timeDiffSig[i] *100;
		printf("%s\t%.2f\t%.2f\t%4.2f\t\t%.0f\t%4.2f\n",timeDiff[i]->GetName(),timeDiffMean[i],timeDiffSig[i],timeDiffRes[i],timeDiff[i]->GetEntries(),timeDiffChisquare[i]);
		timeDiffLegend->AddEntry(timeDiff[i],Form("ch %i Time-Resolution: %.0f ps Mean: %4.2f Sigma: %4.2f Entries: %4.2f Chi2: %4.2f",i,timeDiffRes[i],timeDiffMean[i],timeDiffSig[i],timeDiff[i]->GetEntries(),timeDiffChisquare[i]),"lf");
	}
  }



}


#endif
