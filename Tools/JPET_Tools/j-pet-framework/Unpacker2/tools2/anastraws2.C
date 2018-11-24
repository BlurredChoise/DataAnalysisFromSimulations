#define anastraws2_cxx
#include "anastraws2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void anastraws2::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L anastraws2.C
//      Root > anastraws2 t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   
   TH2F *ttot = new TH2F("ttot","tot all channels",400,0.,400.,32,0,31);
   TH1F *drift_ch[32];
   
   for(int i = 0; i < 32; i++) {
    drift_ch[i] = new TH1F(Form("drift_ch_%d", i), Form("Individual drift channel %d", i), 90000, 0, 90000);
   }

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     if (jentry%1000 == 0) {cerr<<jentry<<endl; }
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
             for (Int_t e_hits=0; e_hits<totalNTDCHits; e_hits++) {
 	if(TDCHits_channel[e_hits]>28)
 	  continue;
	
 	Float_t tot=0.0;
	
	drift_ch[TDCHits_channel[e_hits]]->Fill(TDCHits_leadTimes[e_hits][0]);
// 	
// 	for (Int_t c_hits=0; c_hits<TDCHits_leadsNum[e_hits]; c_hits++) {
// 
// 	  drift_ch[TDCHits_channel[e_hits]]->Fill(TDCHits_leadTimes[e_hits][c_hits]);
// 	  
//  		  tot = 0.1*(TDCHits_leadTimes[e_hits][c_hits]); //-tt_offset[Hits_channel[e_hits]];
//  	      ttot->Fill(tot,TDCHits_channel[e_hits]);
// 
// 	}
	     }
      
      
      
      
      
      
      
      
      
   }
}
