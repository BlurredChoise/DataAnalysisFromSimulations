#define generate_corrections_TRB3_experimental_cxx
// The class definition in generate_corrections_TRB3_experimental_experimental.h has been generated automatically
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
// Root > T->Process("generate_corrections_TRB3_experimental_experimental.C")
// Root > T->Process("generate_corrections_TRB3_experimental_experimental.C","some options")
// Root > T->Process("generate_corrections_TRB3_experimental_experimental.C+")
//

#include "generate_corrections_TRB3_experimental.h"
#include <TH2.h>
#include <TStyle.h>


TH1F** binsHist;
TH1F** correctionsHist;

int channelCount = 192;

void generate_corrections_TRB3_experimental::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   
   binsHist = new TH1F*[channelCount];
   correctionsHist = new TH1F*[channelCount];
   for(int i = 0; i < channelCount; i++){
     binsHist[i] = new TH1F(Form("binsHist%d", i), Form("binsHist%d", i), 500, 0, 5000);
     correctionsHist[i] = new TH1F(Form("correction%d", i), Form("correction%d", i), 500, 0, 500);
   }
     
  }

void generate_corrections_TRB3_experimental::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t generate_corrections_TRB3_experimental::Process(Long64_t entry)
{
  b_event_totalNTDCHits->GetEntry(entry);
  b_event_TDCHits_->GetEntry(entry);

  
  if (entry % 10000 == 0)
    cerr<<entry<<endl;
  
  for(int i = 0; i < totalNTDCHits; i++) {
    if (TDCHits_channel[i] != 0 && TDCHits_channel[i] != 65 && TDCHits_channel[i] != 130 && TDCHits_channel[i] != 195) {
      binsHist[TDCHits_channel[i]]->Fill(TDCHits_leadFineTime1[i]);
    }
  }
  
  return kTRUE;
}

void generate_corrections_TRB3_experimental::SlaveTerminate()
{
  for(int i = 0; i < channelCount; i++)
    binsHist[i]->Scale(5000. / binsHist[i]->Integral(0, 5000));

  
  for(int i = 0; i < channelCount; i++){
    float sum=0;
    
    for(int j = 0; j < 32 ; j++)
     correctionsHist[i]->SetBinContent(j,sum);
      
    for(int j = 32; j < 500 ; j++){
      sum += binsHist[i]->GetBinContent(j);
      
      correctionsHist[i]->SetBinContent(j,sum);
    }
  }
   
  //filling linear corrections for reference channels
  for(int i = 0; i < 500; i++) {
    correctionsHist[0]->SetBinContent(i, i*10);
    correctionsHist[48]->SetBinContent(i, i*10);
    correctionsHist[95]->SetBinContent(i, i*10);
    correctionsHist[143]->SetBinContent(i, i*10);
  }
}

void generate_corrections_TRB3_experimental::Terminate()
{
  TCanvas *canvi =new TCanvas ("can1","can1",1300,1200);
  canvi->Divide(2,2);
  canvi->cd(1);
  correctionsHist[9]->Draw();
  canvi->cd(2);
  binsHist[9]->Draw();
  canvi->cd(3);
  binsHist[11]->Draw();
  canvi->cd(4);
  binsHist[12]->Draw();
  
  TFile *outputFile = new TFile("./correctionFile.root", "recreate" );
  outputFile->cd();
  for(int i = 0; i < channelCount; i++){
    correctionsHist[i]->Write();
  }
  outputFile->Close();
  
}
