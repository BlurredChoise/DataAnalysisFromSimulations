#define analyze_hits_cxx
// The class definition in analyze_hits.h has been generated automatically
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
// Root > T->Process("analyze_hits.C")
// Root > T->Process("analyze_hits.C","some options")
// Root > T->Process("analyze_hits.C+")
//

#include "analyze_hits.h"
#include <TH2.h>
#include <TStyle.h>

TH1F* diff_ch1_ch2;


void analyze_hits::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

		diff_ch1_ch2 = new TH1F("diff_ch1_ch2", "diff_ch1_ch2", 20000000, -10000, 10000);

}

void analyze_hits::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t analyze_hits::Process(Long64_t entry)
{
		b_eventIII_totalNTDCChannels->GetEntry(entry);
		b_eventIII_TDCChannels_->GetEntry(entry);


		double ch1=0;
		double ch2=0;

	for (int i = 0; i < totalNTDCChannels; i++) {
				if (TDCChannels_channel[i] == 1) { ch1 = TDCChannels_leadTime1[i];
	/*				for (int j = 0; j < TDCHits_leadsNum[i]; j++)
						leads_ch1[j] = TDCHits_leadTimes[i][j];
					for (int j = 0; j < TDCHits_trailsNum[i]; j++)
						trails_ch1[j] = TDCHits_trailTimes[i][j];*/
				}		
				else if (TDCChannels_channel[i] == 3) { ch2 = TDCChannels_leadTime1[i];
	/*				for (int j = 0; j < TDCHits_leadsNum[i]; j++)
						leads_ch2[j] = TDCHits_leadTimes[i][j];
					for (int j = 0; j < TDCHits_trailsNum[i]; j++)
						trails_ch2[j] = TDCHits_trailTimes[i][j];*/
				}
			}

if (ch1 != -100000 && ch2 != -100000 && ch1 != 0 && ch2 != 0)
	diff_ch1_ch2->Fill(ch1 - ch2);
   return kTRUE;
}

void analyze_hits::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void analyze_hits::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
