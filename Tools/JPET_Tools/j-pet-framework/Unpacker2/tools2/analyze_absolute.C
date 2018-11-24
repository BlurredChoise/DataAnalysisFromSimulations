#define analyze_absolute_cxx
// The class definition in analyze_absolute.h has been generated automatically
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
// Root > T->Process("analyze_absolute.C")
// Root > T->Process("analyze_absolute.C","some options")
// Root > T->Process("analyze_absolute.C+")
//

#include "analyze_absolute.h"
#include <TH2.h>
#include <TStyle.h>

TH1F* diff_ch1_ch2;
TH1F* tot1;
TH1F* tot2;




void analyze_absolute::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

	diff_ch1_ch2 = new TH1F("diff_ch1_ch2", "diff_ch1_ch2", 20000000, -10000, 10000);
	tot1 = new TH1F("tot_ch1", "tot_ch1", 10000000, -5000, 5000);
	tot2 = new TH1F("tot_ch2", "tot_ch2", 10000000, -5000, 5000);


   TString option = GetOption();

}

void analyze_absolute::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t analyze_absolute::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either analyze_absolute::GetEntry() or TBranch::GetEntry()
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

	b_event_totalNTDCHits->GetEntry(entry);
		b_event_TDCHits_->GetEntry(entry);


	double ch1=0;
	double ch2=0;

for (int i = 0; i < totalNTDCHits; i++) {
			if (TDCHits_channel[i] == 1) { ch1 = TDCHits_absoluteTimeLine[i][0];
				tot1->Fill(TDCHits_absoluteTimeLine[i][1] - TDCHits_absoluteTimeLine[i][0] );
/*				for (int j = 0; j < TDCHits_leadsNum[i]; j++)
					leads_ch1[j] = TDCHits_leadTimes[i][j];
				for (int j = 0; j < TDCHits_trailsNum[i]; j++)
					trails_ch1[j] = TDCHits_trailTimes[i][j];*/
			}		
			else if (TDCHits_channel[i] == 3) { ch2 = TDCHits_absoluteTimeLine[i][0];
				tot2->Fill(TDCHits_absoluteTimeLine[i][1] - TDCHits_absoluteTimeLine[i][0] );
/*				for (int j = 0; j < TDCHits_leadsNum[i]; j++)
					leads_ch2[j] = TDCHits_leadTimes[i][j];
				for (int j = 0; j < TDCHits_trailsNum[i]; j++)
					trails_ch2[j] = TDCHits_trailTimes[i][j];*/
			}
		}

diff_ch1_ch2->Fill(ch1 - ch2);



   return kTRUE;
}

void analyze_absolute::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void analyze_absolute::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
