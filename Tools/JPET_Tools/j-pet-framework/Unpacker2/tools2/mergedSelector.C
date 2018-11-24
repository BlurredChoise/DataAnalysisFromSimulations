#define mergedSelector_cxx
// The class definition in mergedSelector.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("mergedSelector.C")
// Root > T->Process("mergedSelector.C","some options")
// Root > T->Process("mergedSelector.C+")
//

#include "mergedSelector.h"
#include <iostream>
#include <iomanip>
#include <math.h>
// Root includes
#include "TObjString.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TObject.h"
#include "TTree.h"
#include "TColor.h"
#include "./bktools.h"


//Int_t isPULSER = 0;    // 0 for Pulser
//Int_t isPULSER = 1;   // 1 for Cosmics or else


// LED-PMT all Channels with FFE2
Int_t   Channels[8] = {   1 ,	// #0    Channel switch 0=off  1=on  
			  1 ,	// #1
			  1 ,	// #2
			  1 ,	// #3
			  1 ,	// #4
			  1 ,	// #5
			  1 ,	// #6
			  1 };  // #7  
 Int_t EntryMax = 46000, sumRangeMin = 2900, sumRangeMax = 4200;
 Int_t sumBinWidth =(sumRangeMax-sumRangeMin)/40;
 Int_t timeDiffRangeMin = 510, timeDiffRangeMax = 550;
 Int_t totRangeMin = 270, totRangeMax = 410;

Int_t ADCthreshold = 520;

TGraph *g[8];
TMultiGraph *mg[8];
Int_t x[128];
Int_t count[8];
//TH1F *hADC;
TH1F *timeDiff[8];
TH1F *tot[8];
TH1F *sums[8];

TF1 *sumsFit[8];
TF1 *timeDiffFit[8];
TF1 *totFit[8];

TH2F *sumVStime[8];
TH2F *sumVSentry[8];
TH2F *tot_vs_timeDiff[8];
TH2F *sumVStot[8];
TH2F *ADCtotVStot[8];

 char buf1[30];
 char buf2[30];
 char buffer[80], buffer2[80]; //Text_t  better  form even better?
Float_t NumOfEvent=0;

Int_t   ChannelColor[8] = {   2 ,  3   ,  4  ,  41   ,  6  ,  7  , 8   ,  9  };  // ColorSelection for Channel #

Int_t  totMaxRange=0, timeDiffMaxRange=0, sumMaxRange=0;

Float_t sumsMean[8], sumsMax[8], sumsSig[8], sumsRes[8];
Double_t  sumsChisquare[8], sumNDF[8];
Float_t timeDiffMean[8], timeDiffMax[8], timeDiffSig[8], timeDiffRes[8];
Double_t  timeDiffChisquare[8], timeDiffNDF[8];
Float_t totMean[8], totMax[8], totSig[8], totRes[8];
Double_t  totChisquare[8], totNDF[8];

void mergedSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void mergedSelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   gROOT->SetStyle("Plain");
   //gStyle->SetOptStat(0);
//   gStyle->SetOptStat(11);
//   gStyle->SetOptFit(11);
   //set_plot_style();
   TString option = GetOption();
   set_nice_color();
   
   for(int i = 0; i <128; i++) x[i] = i; // prepare scale X

 for (int j = 0; j < 8; j++) {

    mg[j] = new TMultiGraph();
    count[j]=0;	
/*

    	sprintf(buf1,"ADC histogram channel %i",j);
    	sprintf(buf2,"ADC histogram channel %i",j);
    	hADC[j] = new TH1F(buf1,buf2,128,0,128);
    	hADC[j]->SetLineColor(j+2);
    	hADC[j]->SetLineWidth(2);
 */

    timeDiff[j] = new TH1F(Form("timeDiff_%i",j),Form("timeDiff_%i",j),TMath::Abs(timeDiffRangeMin-timeDiffRangeMax),timeDiffRangeMin,timeDiffRangeMax);
    setOPT_hists(timeDiff[j], "TDC Channels [100ps]", "Counts",510,1,1.3,j,timeDiffRangeMin,timeDiffRangeMax);

    timeDiffFit[j] = new TF1(Form("timeDiffFit[%i]",j),GaussFitFunc2,timeDiffRangeMin,timeDiffRangeMax,3);
    setOPT_func(timeDiffFit[j],1,2,j);

    tot[j] = new TH1F(Form("tot_%i",j),Form("time over threshold %i",j),TMath::Abs(totRangeMin-totRangeMax),totRangeMin,totRangeMax);
    setOPT_hists(tot[j], "TDC Channels [100ps]", "Counts",510,1,1.3,j,totRangeMin,totRangeMax);

    totFit[j] = new TF1(Form("totFit[%i]",j),GaussFitFunc2,totRangeMin,totRangeMax,3);
    setOPT_func(totFit[j],1,2,j);

    sums[j] = new TH1F(Form("Sum distribution ch.%i",j),Form("Sum distribution ch.%i",j),sumBinWidth, sumRangeMin, sumRangeMax);
    setOPT_hists(sums[j], "ADC (arb. unit)", "Counts",510,1,1.3,j,sumRangeMin,sumRangeMax);

    sumsFit[j] = new TF1(Form("sumsFit[%i]",j),GaussFitFunc2,sumRangeMin,sumRangeMax,3);
    setOPT_func(sumsFit[j],1,2,j);



    tot_vs_timeDiff[j] = new TH2F(Form("tot_vs_timeDiff_%i",j),Form("tot vs time Diff %i",j), TMath::Abs(totRangeMin-totRangeMax),totRangeMin,totRangeMax,TMath::Abs(timeDiffRangeMin-timeDiffRangeMax),timeDiffRangeMin,timeDiffRangeMax);
    setOPT_hists(tot_vs_timeDiff[j],"TDC Channels [100ps]", "TDC Channels [100ps]",510,8,0.4,j,timeDiffRangeMin,timeDiffRangeMax,totRangeMin,totRangeMax);

    sumVStime[j] = new TH2F(Form("Sum versus timeDiff ch.%i",j),Form("Sum versus timeDiff ch.%i",j),TMath::Abs(timeDiffRangeMin-timeDiffRangeMax),timeDiffRangeMin,timeDiffRangeMax,sumBinWidth, sumRangeMin, sumRangeMax);
    setOPT_hists(sumVStime[j], "TDC Channels [100ps]","Sums ADC (arb. unit)",510,8,0.4,j,sumRangeMin,sumRangeMax ,timeDiffRangeMin,timeDiffRangeMax);

    sumVStot[j] = new TH2F(Form("Sum versus tot ch.%i",j),Form("Sum versus tot ch.%i",j),TMath::Abs(totRangeMin-totRangeMax),totRangeMin,totRangeMax,sumBinWidth, sumRangeMin, sumRangeMax);
    setOPT_hists(sumVStot[j], "TDC Channels [100ps]","Sums ADC (arb. unit)",510,8,0.4,j,sumRangeMin,sumRangeMax , totRangeMin,totRangeMax);

    ADCtotVStot[j] = new TH2F(Form("ADCtot versus tot ch.%i",j),Form("ADCtot versus tot ch.%i",j),TMath::Abs(totRangeMin-totRangeMax),totRangeMin,totRangeMax,TMath::Abs(totRangeMin-totRangeMax),totRangeMin,totRangeMax);
    setOPT_hists(ADCtotVStot[j], "TDC Channels [100ps]","ADC Bins [50ns]",510,8,0.4,j,totRangeMin,totRangeMax, totRangeMin,totRangeMax);

    sumVSentry[j] = new TH2F(Form("Sum versus entry ch.%i",j),Form("Sum versus entry ch.%i",j),EntryMax/30,0,EntryMax,sumBinWidth, sumRangeMin, sumRangeMax);
    setOPT_hists(sumVSentry[j],"Entries","ADC (arb. unit)",510,8,0.4,j,sumRangeMin, sumRangeMax, 0,EntryMax);

 }

}

Bool_t mergedSelector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either mergedSelector::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

	b_merged_event_totalNTDCHits->GetEntry(entry);
	b_merged_event_TDCHits_->GetEntry(entry);
	b_merged_event_ADCHits_->GetEntry(entry);
	//b_merged_event_referenceTime->GetEntry(entry);
	//b_Hits_samples->GetEntry(entry);

	  Float_t leadTimeCh[8]=-1.;
	  Float_t leadTimeCh33=-1., leadTimeCh31=-1., leadTimeCh63=-1.;
	  Float_t trailTimeCh[8]=-1.;

	  NumOfEvent++;

	 // cout <<NumOfEvent<<endl;

         for (Int_t i=0.; i < 50.; i++) {

	  if(NumOfEvent==(1000*i)) printf(" Event number: %d\n",NumOfEvent);
	 }



	for(int i = 0; i < totalNTDCHits; i++) {
	  for(int j = 0; j < 8; j++) {

	  if (TDCHits_channel[i] == j) {
	    leadTimeCh[j] = TDCHits_leadTime1[i];
	    trailTimeCh[j] = TDCHits_trailTime1[i];
	  }
	  else if (TDCHits_channel[i] == 49) {
	    leadTimeCh33 = TDCHits_leadTime1[i];
	  }
	  else if (TDCHits_channel[i] == 31) {
	    leadTimeCh31 = TDCHits_leadTime1[i];
	  }
	  else if (TDCHits_channel[i] == 63) {
	    leadTimeCh63 = TDCHits_leadTime1[i];
	    //cout<<Hits_leadTime1[i]<<endl;
	  }
        }
      }

 for(int j = 0; j < 8; j++) {
   if(leadTimeCh[j] > 0) tot[j]->Fill(TMath::Abs(leadTimeCh[j] - trailTimeCh[j]));
   if(leadTimeCh[j] > 0) timeDiff[j]->Fill(TMath::Abs(leadTimeCh[j] - leadTimeCh33));

 //  if(leadTimeCh[j] > 0) cout<<"leadTimeCh"<<leadTimeCh[j]<<"trailTimeCh"<<trailTimeCh[j]<<endl;
 }

	Int_t y[128];
	Int_t sum[8];
	Int_t baseline[8];
	Int_t ADCtot[0];	
	Float_t ADCtotCount = 0;
 
	for(int j = 0; j < 8; j++) {

          baseline[j]=0.;
	  for (int i = 0; i < 128; i++) {

  
//	  if ((ADCHits_samples[j][i] < 0) || (ADCHits_samples[j][i] > 1013)) return kTRUE;
	  if ((ADCHits_samples[j][i] < 0) || (ADCHits_samples[j][i] > 1500)) return kTRUE;	  
	  if ((ADCHits_samples[j][i] > ADCthreshold ) || (ADCtotCount = 0)) {
		ADCtotCount = i;
	  }
	  if ((ADCHits_samples[j][i] < ADCthreshold ) || (ADCtotCount != 0)) {
		ADCtotCount = TMath::Abs(ADCtotCount - i);
	  }
		y[i] = ADCHits_samples[j][i];

		if(i>1&&i<18) baseline[j] += ADCHits_samples[j][i]*12./16.;
		//if (baseline[0]>1 || i == 32 || j == 0) cout << baseline[0] <<endl;
		if(i>18&&i<31) sum[j] += ADCHits_samples[j][i];
		// if (sum[0]>1 || i == 32 || j == 0) cout <<sum[0]<<endl;
	  }  // end i loop
	  if(leadTimeCh[j] > 0)  {
		count[j]++;
		if (count[j] < 100) {    //limit on number of waves

//			hADC->Reset();
		  	for (int i = 1; i < 128; i++) {
// cout<<"count"<<count[j]<<endl;
// cout<<"ADC input"<<hADC->GetBinContent(i)<<endl;
//				hADC->Fill(i, ADCHits_samples[j][i]);
// cout<<"ADC output"<<hADC->GetBinContent(i)<<endl;
			}
			g[j] = new TGraph(128, x, y);
			g[j]->SetLineColor(j+2);
			mg[0]->Add(g[j]);
//    			hADC->SetLineColor(j+2);
//			hsADC->Add(hADC);
	  	}

	  	if(sum[j] - baseline[j] > 100) {
		sums[j]->Fill(sum[j] -  baseline[j]);
             // cout<<baseline[1]<<endl;
                //cout<<"count"<<count[j]<<"timeDiff   "<<TMath::Abs(leadTimeCh[j] - leadTimeCh33)<<endl;
                //cout<<"count"<<count[j]<<"tot    "<<TMath::Abs(leadTimeCh[j] - trailTimeCh[j])<<endl;
          	sumVStime[j]->Fill(TMath::Abs(leadTimeCh[j] - leadTimeCh33), sum[j] - baseline[j]);
          	sumVStot[j]->Fill(TMath::Abs(leadTimeCh[j] - trailTimeCh[j]), sum[j] - baseline[j]);
          	tot_vs_timeDiff[j]->Fill(TMath::Abs(leadTimeCh[j] - trailTimeCh[j]), TMath::Abs(leadTimeCh[j] - leadTimeCh33));
          	ADCtotVStot[j]->Fill(TMath::Abs(leadTimeCh[j] - trailTimeCh[j]), ADCtotCount );
		sumVSentry[j]->Fill(entry,sum[j] - baseline[j]);
		}

          	sum[j]=0., leadTimeCh[j]=-1., baseline[j]=0.;
	  }
	} //end j loop


   return kTRUE;
}

void mergedSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void mergedSelector::Terminate()
{
  TString filename = gROOT->GetListOfFiles()->At(0)->GetName();
// if (!chain) {}
// else {
//   TString filename = chain.GetListOfFiles()->At(0)->GetTitle();
// }

TObjArray *arr = filename.Tokenize("/.");
TString bla = "";
for(Int_t i=0; i<arr->GetEntriesFast(); i++) {
	bla = arr->At(i)->GetName();
	if(bla.Contains("ec1")) {
		bla.ReplaceAll("ec","");
		break;
	}	
}

printf("%s  %s \n",filename.Data(),bla.Data()); 


    //wave histograms

         TCanvas *a = new TCanvas(Form("%s_waves",bla.Data()), "waves", 200, 10, 1000, 800);
	 setOPT_canvas(a);

	 int first = 0;
	 for(int j = 0; j < 8; j++) {
	    if (Channels[j] == 1) {
		if  (first == 0) {
			first = 1;
			mg[j]->Draw("ALP");
		}
	    	else {
			mg[j]->Draw("ALP same");
	    	}
	    }
	 }

//	a->BuildLegend();


    //ADC histograms

//         TCanvas *b = new TCanvas("b", "ADC histograms", 200, 10, 1200, 1000);

//  	 for(int i = 0; i < 100; i++) {
// 		for(int j = 0; j < 8; j++) {
// 			hsADC->Add(b[j][i]);
// 		}
// 	 }
// 	 b->Draw("e1p");


printf("%s \n", "fit params\n");  



printf("%s \n", "\t\t\tmean\tsigma\tresolution\tentries\n");
printf("%s \n", "Time Resolution\n"); 	 	 
	 TCanvas  *c = new TCanvas(Form("%s_timeDiff",bla.Data()), "timeDiff", 200, 10, 1000, 800);
	 setOPT_canvas(c);

         TLegend *timeDiffLegend = new TLegend(0.13,0.75,0.52,0.94);
         myLegendSetUp(timeDiffLegend,0.02);

//	 Format_hist(timeDiff,"", 1.3);
	 for(int j = 0; j < 8; j++) {
	      if (Channels[j] == 1) { 	// if channel on
	 	 if (timeDiffMaxRange < timeDiff[j]->GetBinContent(timeDiff[j]->GetMaximumBin())) timeDiffMaxRange = timeDiff[j]->GetBinContent(timeDiff[j]->GetMaximumBin());
	   }	
	 }

	 timeDiffMaxRange = timeDiffMaxRange * 1.3;

	 for(int j = 0; j < 8; j++) {
	 timeDiff[j]->SetTitle("");
	 timeDiff[j]->GetYaxis()->SetRangeUser(0,timeDiffMaxRange);
	 }

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
		timeDiffFit[i]->ReleaseParameter(n);
		timeDiffFit[i]->SetParameter(n,0.0);
	    }

		timeDiffFit[i]->SetParName(0,"Const");
		timeDiffFit[i]->SetParName(1,"Mean");
		timeDiffFit[i]->SetParName(2,"Sigma");

	    if(sums[i]->GetEntries()>300)
	    {
		timeDiffFit[i]->SetParameter(0,timeDiff[i]->GetMaximum());
		timeDiffFit[i]->SetParameter(1,timeDiffMean[i]);
		timeDiffFit[i]->SetParameter(2,timeDiffSig[i]);

		timeDiffFit[i]->SetRange(timeDiffRangeMin, timeDiffRangeMax);
		timeDiff[i]->Fit(Form("timeDiffFit[%i]",i),"+Q0","",timeDiffRangeMin, timeDiffRangeMax);
		timeDiff[i]->Fit(Form("timeDiffFit[%i]",i),"+Q","",timeDiffRangeMin, timeDiffRangeMax);		timeDiffMean[i]=timeDiffFit[i]->GetParameter(1);
		timeDiffSig[i]=timeDiffFit[i]->GetParameter(2);
		timeDiffChisquare[i]=timeDiffFit[i]->GetChisquare();



	    }
	}

    		timeDiffRes[i] = timeDiffSig[i] *100;
		printf("%s\t%.2f\t%.2f\t%4.2f\t\t%.0f\t%4.2f\n",timeDiff[i]->GetName(),timeDiffMean[i],timeDiffSig[i],timeDiffRes[i],timeDiff[i]->GetEntries(),timeDiffChisquare[i]);
		timeDiffLegend->AddEntry(timeDiff[i],Form("ch %i Time-Resolution: %.0f ps Mean: %4.2f Sigma: %4.2f Entries: %4.2f Chi2: %4.2f",i,timeDiffRes[i],timeDiffMean[i],timeDiffSig[i],timeDiff[i]->GetEntries(),timeDiffChisquare[i]),"lf");
	}
  }
	 int first = 0;
	 for(int j = 0; j < 8; j++) {
	    if (Channels[j] == 1) {
		if  (first == 0) {
			first = 1;
			timeDiff[j]->Draw();
		}
	    	else {
		timeDiff[j]->Draw("same");
	    	}
	    }
	 }
	 //c->BuildLegend();
  	timeDiffLegend->Draw();

//---------------------------
//------- Time over Threshold
//---------------------------

	 TCanvas  *d = new TCanvas(Form("%s_tot",bla.Data()), "Time over Threshold", 200, 10, 1000, 800);
	 setOPT_canvas(d);

         TLegend *totLegend = new TLegend(0.13,0.75,0.52,0.94);
         myLegendSetUp(totLegend,0.02);

	 for(int j = 0; j < 8; j++) {
	      if (Channels[j] == 1) { 	// if channel on
	 	 if (totMaxRange < tot[j]->GetBinContent(tot[j]->GetMaximumBin())) totMaxRange = tot[j]->GetBinContent(tot[j]->GetMaximumBin());
	   }	
	 }

	 totMaxRange = totMaxRange * 1.3;

	 for(int j = 0; j < 8; j++) {
	 tot[j]->SetTitle("");
	 tot[j]->GetYaxis()->SetRangeUser(0,totMaxRange);
	 }

  for (int i = 0; i < 8; i++) {

     if (Channels[i] == 1) {
	if(tot[i]->GetEntries() > 0)
	{	
	totMean[i]=tot[i]->GetMean();
	totMax[i]=tot[i]->GetBinCenter(tot[i]->GetMaximumBin());
	totSig[i]=tot[i]->GetRMS();

            //Fitting
	    for(Int_t n=0; n<3; n++)
	    {
		totFit[i]->ReleaseParameter(n);
		totFit[i]->SetParameter(n,0.0);
	    }

		totFit[i]->SetParName(0,"Const");
		totFit[i]->SetParName(1,"Mean");
		totFit[i]->SetParName(2,"Sigma");

	    if(sums[i]->GetEntries()>300)
	    {
		totFit[i]->SetParameter(0,tot[i]->GetMaximum());
		totFit[i]->SetParameter(1,totMax[i]);
		totFit[i]->SetParameter(2,totSig[i]);

		totFit[i]->SetRange(totRangeMin, totRangeMax);
		tot[i]->Fit(Form("totFit[%i]",i),"+Q0","",totRangeMin, totRangeMax);		tot[i]->Fit(Form("totFit[%i]",i),"+Q","",totRangeMin, totRangeMax);		
		totMean[i]=totFit[i]->GetParameter(1);
		totSig[i]=totFit[i]->GetParameter(2);
		totChisquare[i]=totFit[i]->GetChisquare();



	    }
	}

    		totRes[i] = totSig[i] *100;
		printf("%s\t%.2f\t%.2f\t%4.2f\t\t%.0f\t%4.2f\n",tot[i]->GetName(),totMean[i],totSig[i],totRes[i],tot[i]->GetEntries(),totChisquare[i]);
		totLegend->AddEntry(tot[i],Form("ch %i Time-Resolution: %.0f ps Mean: %4.2f Sigma: %4.2f Entries: %4.2f Chi2: %4.2f",i,totRes[i],totMean[i],totSig[i],tot[i]->GetEntries(),totChisquare[i]),"lf");
	}
  }
	 int first = 0;
	 for(int j = 0; j < 8; j++) {
	    if (Channels[j] == 1) {
		if  (first == 0) {
			first = 1;
			tot[j]->Draw();
		}
	    	else {
		tot[j]->Draw("same");
	    	}
	    }
	 }
	 //d->BuildLegend();
  	totLegend->Draw();




    //---------------
    //sums histograms
    //---------------

printf("%s \n", "Energy Resolution\n");
printf("%s \n", "\t\t\tmean\tsigma\tresolution\tentries\tchi2\n");

	 TCanvas *e = new TCanvas(Form("%s_sums",bla.Data()), "sums", 200, 10, 1000, 800);
	 setOPT_canvas(e);

         TLegend *sumsLegend = new TLegend(0.13,0.75,0.52,0.94);
         myLegendSetUp(sumsLegend,0.02);



	 for(int j = 0; j < 8; j++) {
	      //cout <<"sumsRangeMax"<<sumsRangeMax<<endl;
	      if (Channels[j] == 1) { 	// if channel on
	 	 if (sumMaxRange < sums[j]->GetBinContent(sums[j]->GetMaximumBin())) sumMaxRange = sums[j]->GetBinContent(sums[j]->GetMaximumBin());
	   }	
	 }

	 sumMaxRange = sumMaxRange * 1.3;
	 //cout <<"sumsRangeMax End"<<sumsRangeMax<<endl;

	 for(int j = 0; j < 8; j++) {
	 sums[j]->SetTitle("");
	 sums[j]->GetYaxis()->SetRangeUser(0,sumMaxRange);
	 }

  for (int i = 0; i < 8; i++) {

     if (Channels[i] == 1) {
//	cout<<"yeeaaa"<<Channels[i]<<endl;
	if(sums[i]->GetEntries() > 0)
	{	
	sumsMean[i]=sums[i]->GetMean();
	sumsMax[i]=sums[i]->GetBinCenter(sums[i]->GetMaximumBin());
	sumsSig[i]=sums[i]->GetRMS();
/*

		cout<<"start Sigma:"<<sumsSig[i]<<"sum Max"<<sumsMax[i]<<"  begin range"<<sumsMax[i]-(sumsSig[i])<<"end range"<<sumsMax[i]+(sumsSig[i])<<endl;
		cout<<"start Sigma:"<<sumsSig[i]/2.35<<"sum Max"<<sumsMax[i]<<"  begin range"<<sumsMax[i]-(sumsSig[i]/2.35)<<"end range"<<sumsMax[i]+(sumsSig[i]/2.35)<<endl;
		cout<<"start Sigma:"<<sumsSig[i]*2<<"sum Max"<<sumsMax[i]<<"  begin range"<<sumsMax[i]-(sumsSig[i]*2)<<"end range"<<sumsMax[i]+(sumsSig[i]*2)<<endl;
*/

            //Fitting
	    for(Int_t n=0; n<3; n++)
	    {
		sumsFit[i]->ReleaseParameter(n);
		sumsFit[i]->SetParameter(n,0.0);
	    }

		sumsFit[i]->SetParName(0,"Const");
		sumsFit[i]->SetParName(1,"Mean");
		sumsFit[i]->SetParName(2,"Sigma");

	    if(sums[i]->GetEntries()>300)
	    {

		sumsFit[i]->SetParameter(0,sums[i]->GetMaximum());
		sumsFit[i]->SetParameter(1,sumsMax[i]);
		sumsFit[i]->SetParameter(2,sumsSig[i]);

//		sumsFit[i]->SetRange(sumsMax[i]-(sumsSig[i]),sumsMax[i]+(sumsSig[i]));
//		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q0","",sumsMax[i]-(sumsSig[i]),sumsMax[i]+(sumsSig[i]));		
//		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q","",sumRangeMin,sumRangeMax);
//		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q",""); //,sumsMax[i]*0.9,sumsMax[i]*1.1);
//		sumsMean[i]=sumsFit[i]->GetParameter(1);
//		sumsSig[i]=sumsFit[i]->GetParameter(2);

// 		cout<<"2  start Sigma:"<<sumsSig[i]<<"sum Max"<<sumsMax[i]<<"  begin range"<<sumsMax[i]-(sumsSig[i])<<"end range"<<sumsMax[i]+(sumsSig[i])<<endl;
// 		cout<<"2  start Sigma:"<<sumsSig[i]/2.35<<"sum Max"<<sumsMax[i]<<"  begin range"<<sumsMax[i]-(sumsSig[i]/2.35)<<"end range"<<sumsMax[i]+(sumsSig[i]/2.35)<<endl;
// 		cout<<"2  start Sigma:"<<sumsSig[i]*2<<"sum Max"<<sumsMax[i]<<"  begin range"<<sumsMax[i]-(sumsSig[i]*2)<<"end range"<<sumsMax[i]+(sumsSig[i]*2)<<endl;


// 		sumsFit[i]->SetRange(sumsMean[i]-(sumsSig[i]),sumsMean[i]+(sumsSig[i]));
// 		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q","",sumsMean[i]-(sumsSig[i]*2),sumsMean[i]+(sumsSig[i]*2));
// 		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q","",sumsMean[i]-(sumsSig[i]/2.35),sumsMean[i]+(sumsSig[i]/2.35));
// 		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q","",sumsMax[i]*0.9,sumsMax[i]*1.1);
		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q0","",sumRangeMin,sumRangeMax);
		sumsFit[i]->SetRange(sumRangeMin,sumRangeMax);
		sums[i]->Fit(Form("sumsFit[%i]",i),"+Q","",sumRangeMin,sumRangeMax);
		sumsMean[i]=sumsFit[i]->GetParameter(1);
		sumsSig[i]=sumsFit[i]->GetParameter(2);
		sumsChisquare[i]=sumsFit[i]->GetChisquare();
		sumNDF[i]=sumsFit[i]->GetNDF();


	    }
	}

    		sumsRes[i] = sumsSig[i] / sumsMean[i] *100;
		printf("%s\t%.2f\t%.2f\t%4.2f\t\t%.0f\t%4.2f\n",sums[i]->GetName(),sumsMean[i],sumsSig[i],sumsRes[i],sums[i]->GetEntries(),sumsChisquare[i]);
		sumsLegend->AddEntry(sums[i],Form("ch %i Energy-Resolution: %4.2f %% Mean: %4.2f Sigma: %4.2f Entries: %4.2f Chi2 / NDF: %4.2f / %4.2f ",i,sumsRes[i],sumsMean[i],sumsSig[i],sums[i]->GetEntries(),sumsChisquare[i],sumNDF[i]),"lf");
//		sumsLegend->AddEntry(sumsFit[i],Form("Fit ch %i Mean: %4.2f Sigma: %4.2f Entries: %4.2f %%",i,sumsMean[i],sumsSig[i],sums[i]->GetEntries()),"f");
	}
  }
	 int first = 0;
	 for(int j = 0; j < 8; j++) {
	    if (Channels[j] == 1) {
		if  (first == 0) {
			first = 1;
	 cout <<"first:  "<<j<<endl;
			sums[j]->Draw();
		}
	    	else {
		sums[j]->Draw("same");
	 cout <<"same:  "<<j<<endl;
	    	}
	    }
	 }
	 //e->BuildLegend();
  	sumsLegend->Draw();


     //sum versus timediff histograms
	 TCanvas *f = new TCanvas(Form("%s_sumVStimeDiff",bla.Data()), "sum versus timediff", 200, 10, 1000, 800);
	 setOPT_canvas(f);

	 sumVStime[0]->Draw("");
	 for(int j = 1; j < 8; j++) {
		sumVStime[j]->Draw("same");
	 }
	f->BuildLegend();


      //sum versus entry histograms
	 TCanvas *g = new TCanvas(Form("%s_sumVSentry",bla.Data()), "sum versus entry", 200, 10, 1000, 800);
	 setOPT_canvas(g);

	 sumVSentry[0]->Draw("");
	 for(int j = 1; j < 8; j++) {
		sumVSentry[j]->Draw("same");
	 }
	g->BuildLegend();

      //sum versus tot histograms
	 TCanvas *k = new TCanvas(Form("%s_sumVStot",bla.Data()), "sum versus tot", 200, 10, 1000, 800);
	 setOPT_canvas(k);

	 int first = 0;
	 for(int j = 0; j < 8; j++) {
	    if (Channels[j] == 1) {
		if  (first == 0) {
			first = 1;
			sumVStot[j]->Draw();
		}
	    	else {
		sumVStot[j]->Draw("same");
	    	}
	    }
	 }
	k->BuildLegend();

      // tot versus timediff histograms
	 TCanvas *l = new TCanvas(Form("%s_totVStimediff",bla.Data()), "tot versus timediff", 200, 10, 1000, 800);
	 setOPT_canvas(l);

	 int first = 0;
	 for(int j = 0; j < 8; j++) {
	    if (Channels[j] == 1) {
		if  (first == 0) {
			first = 1;
			tot_vs_timeDiff[j]->Draw();
		}
	    	else {
		tot_vs_timeDiff[j]->Draw("same");
	    	}
	    }
	 }
	l->BuildLegend();

      // ADCtot versus tot histograms
	 TCanvas *m = new TCanvas(Form("%s_ADCtotVStot",bla.Data()), "ADCtot versus tot", 200, 10, 1000, 800);
	 setOPT_canvas(m);

	 int first = 0;
	 for(int j = 0; j < 8; j++) {
	    if (Channels[j] == 1) {
		if  (first == 0) {
			first = 1;
			ADCtotVStot[j]->Draw();
		}
	    	else {
		ADCtotVStot[j]->Draw("same");
	    	}
	    }
	 }
	m->BuildLegend();

      //TString dst_filename  = filename(filename.Last('/') + 1, filename.Last('.') - filename.Last('/') - 1);
      //cout <<"DSTFileName: "<<dst_filename <<endl;

//	bla = "./out/" + bla;
//        printf("%s   \n",bla.Data());
	a->Print(Form("%s_waves.png",bla.Data()));
 	c->Print(Form("%s_timeDiff.png",bla.Data()));
 	d->Print(Form("%s_tot.png",bla.Data()));
 	e->Print(Form("%s_sums.png",bla.Data()));
 	f->Print(Form("%s_sumVStimeDiff.png",bla.Data()));
 	g->Print(Form("%s_sumVSentry.png",bla.Data()));
 	k->Print(Form("%s_sumVStot.png",bla.Data()));
 	l->Print(Form("%s_totVStimediff.png",bla.Data()));
 	m->Print(Form("%s_ADCtotVStot.png",bla.Data()));

/*
	bla+=".pdf";
 	a->Print(Form("%s(",bla.Data()),"Title:wave histograms");
 	c->Print(bla.Data(),"Title:timesDiff histograms");
 	d->Print(bla.Data(),"Title:tot histograms");
 	e->Print(bla.Data(),"Title:sums histograms");
 	f->Print(bla.Data(),"Title:sum versus timeDiff");
 	g->Print(bla.Data(),"Title:sum versus entry");
 	k->Print(bla.Data(),"Title:sum versus tot");
 	l->Print(Form("%s)",bla.Data()),"Title:tot versus timeDiff");

*/

/*
TFile *out = new TFile("histograms.root","recreate");


 for(int j = 0; j < 8; j++) {
   mg[j] ->Write();
   sums[j] ->Write();
   timeDiff[j] ->Write();
   sumVStime[j]->Write();
   sumVSentry[j]->Write();
 }

 out->Close();*/
	 
}
