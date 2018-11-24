#include "../Unpacker2/EventIII.h"
#include "../Unpacker2/TDCHitIII.h"
#include "../Unpacker2/Event.h"
#include "../Unpacker2/TDCHit.h"
#include "../Unpacker2/TDCHitExtended.h"
#include "../Unpacker2/TDCChannel.h"
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TH2F.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TStyle.h>


#define CHANNELS_NUMBER 100

TH1F* tot_hist[CHANNELS_NUMBER];
TH1F* mult_hist[CHANNELS_NUMBER];
TH2F* tot_mult_hist[CHANNELS_NUMBER];
TH2F* tot_barcode;

int generate_diag_histo_panda(int eventsNum, const char* fileName, int referenceChannel)
{
  TChain chain("T");
  chain.Add(fileName);
    
  EventIII* pEvent = 0;
  TDCChannel* pHit = 0;
  TClonesArray* pArray = 0;
  chain.SetBranchAddress("eventIII", &pEvent);

	string newFileName(fileName);
	newFileName = newFileName.substr(0, newFileName.size() - 5);
	newFileName += "_histos.root";

	TFile* new_file = new TFile(newFileName.c_str(), "RECREATE");
	new_file->cd();
  
  Int_t entries = (Int_t)chain.GetEntries();
  cout<<"Entries = " <<entries<<endl;

	// ------ create histograms 
		// tot histograms created with 1us width
	for (int i = 0; i < CHANNELS_NUMBER; i++) { tot_hist[i] = new TH1F(Form("tot_hist_ch%d", i), Form("tot_hist_ch%d", i), 10000, 0, 1000); }
		// tot vs multiplicity
	for (int i = 0; i < CHANNELS_NUMBER; i++) { tot_mult_hist[i] = new TH2F(Form("tot_mult_hist_ch%d", i), Form("tot_mult_hist_ch%d", i), 10000, 0, 1000, 128, 0, 128); }
		// multiplicity
	for (int i = 0; i < CHANNELS_NUMBER; i++) { mult_hist[i] = new TH1F(Form("mult_hist_ch%d", i), Form("mult_hist_ch%d", i), 128, 0, 128); }
		// tot barcode over channels
	tot_barcode = new TH2F("tot_barcode", "tot_barcode", 10000, 0, 1000, CHANNELS_NUMBER, 0, CHANNELS_NUMBER);
	

	// ------ loop over events
  for(Int_t i = 0; i < entries; i++)
	{
    if (i % 10000 == 0) cout<<i<<endl;
    if (i == eventsNum) break;
    chain.GetEntry(i);
    pArray = pEvent->GetTDCChannelsArray();
    if (pArray == 0) continue;
    TIter iter(pArray);

		double refTime = -100000;

		// ------ loop over channels
    while( pHit = (TDCChannel*) iter.Next() )
		{
			// fetch the ref time
			if (pHit->GetChannel() == referenceChannel) {
				refTime = pHit->GetLeadTime1();
			}

			// fill the tot histograms with the first hits on channels
			//tot_hist[pHit->GetChannel()]->Fill(pHit->GetTOT1());

			// fill the tot histograms with all the hits on channels
			for(int j = 0; j < pHit->GetMult(); j++) { tot_hist[pHit->GetChannel()]->Fill(pHit->GetTOT(j)); }

			// fill the tot vs multiplicity histograms
			for(int j = 0; j < pHit->GetMult(); j++) { tot_mult_hist[pHit->GetChannel()]->Fill(pHit->GetTOT(j), j); }

			// fill the tot barcode histogram
			for(int j = 0; j < pHit->GetMult(); j++) { tot_barcode->Fill(pHit->GetTOT(j), pHit->GetChannel()); }

			// fill the multiplicity histograms
			mult_hist[pHit->GetChannel()]->Fill(pHit->GetMult());
		}
	}

	// ------ adjust histograms
	for (int i = 0; i < CHANNELS_NUMBER; i++) {
		// tot histograms centered at mean and +- 5ns offsets
		tot_hist[i]->GetXaxis()->SetRangeUser(tot_hist[i]->GetMean(1) - 5, tot_hist[i]->GetMean(1) + 5);
		tot_mult_hist[i]->GetXaxis()->SetRangeUser(tot_hist[i]->GetMean(1) - 100, tot_hist[i]->GetMean(1) + 100);
	}
	tot_barcode->GetXaxis()->SetRangeUser(tot_hist[1]->GetMean(1) - 100, tot_hist[1]->GetMean(1) + 100);

	// ------ draw fits
	for (int i = 0; i < CHANNELS_NUMBER; i++) {
		tot_hist[i]->Fit("gaus");
	}

	// ------ saving histograms
	for (int i = 0; i < CHANNELS_NUMBER; i++) { tot_hist[i]->Write();	}
	for (int i = 0; i < CHANNELS_NUMBER; i++) { mult_hist[i]->Write(); }


	return 0;
}
