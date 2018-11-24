#define generate_corrections_TRB3_cxx

#include "generate_corrections_TRB3.h"
#include <TH2.h>
#include <TStyle.h>


TH1F** binsHist;
TH1F** correctionsHist;

int channelCount = 360;

void generate_corrections_TRB3::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   
   binsHist = new TH1F*[channelCount];
   correctionsHist = new TH1F*[channelCount];
   for(int i = 0; i < channelCount; i++){
     binsHist[i] = new TH1F(Form("binsHist%d", i), Form("binsHist%d", i), 500, 0, 500);
     correctionsHist[i] = new TH1F(Form("correction%d", i), Form("correction%d", i), 500, 0, 500);
   }
     
     
  }

void generate_corrections_TRB3::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t generate_corrections_TRB3::Process(Long64_t entry)
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

void generate_corrections_TRB3::SlaveTerminate()
{
  for(int i = 0; i < channelCount; i++)
    binsHist[i]->Scale(5000. / binsHist[i]->Integral(0, 500));

  
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
    correctionsHist[65]->SetBinContent(i, i*10);
    correctionsHist[130]->SetBinContent(i, i*10);
    correctionsHist[195]->SetBinContent(i, i*10);
  }
}

void generate_corrections_TRB3::Terminate()
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
