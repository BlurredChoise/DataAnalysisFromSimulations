//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jan 18 14:30:32 2013 by ROOT version 5.26/00
// from TTree newT/Merged tree
// found on file: /home/shower/ec12339165318.hld.root_merged.root
//////////////////////////////////////////////////////////

#ifndef mergedSelector_h
#define mergedSelector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
   const Int_t kMaxTDCHits = 7;
   const Int_t kMaxADCHits = 8;

class mergedSelector : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
 //MergedEvent     *merged_event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           TDCHits_;
   UInt_t          TDCHits_fUniqueID[kMaxTDCHits];   //[TDCHits_]
   UInt_t          TDCHits_fBits[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_channel[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_TDC[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_nHits[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_width_wk[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_leadTime1[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_trailTime1[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_leadTime2[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_trailTime2[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_leadTime3[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_trailTime3[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_leadTime4[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_trailTime4[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_spikesCtr[kMaxTDCHits];   //[TDCHits_]
   Int_t           ADCHits_;
   UInt_t          ADCHits_fUniqueID[kMaxADCHits];   //[ADCHits_]
   UInt_t          ADCHits_fBits[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_channel[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_ADC[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_nHits[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_samples[kMaxADCHits][128];   //[ADCHits_]
   Int_t           ADCHits_dsp_sum[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_dsp_mean[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_dsp_cf_a[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_dsp_cf_b[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_dsp_cf_t[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_localPtr[kMaxADCHits];   //[ADCHits_]
   Int_t           kMaxMult;
   Int_t           kMaxChannelNr;
   UInt_t          subEvtId;
   Int_t           errors_per_event;
   Int_t           referenceChannel;
   Int_t           referenceTime;
   Int_t           totalNTDCHits;
   Int_t           totalNADCHits;

   // List of branches
   TBranch        *b_merged_event_fUniqueID;   //!
   TBranch        *b_merged_event_fBits;   //!
   TBranch        *b_merged_event_TDCHits_;   //!
   TBranch        *b_TDCHits_fUniqueID;   //!
   TBranch        *b_TDCHits_fBits;   //!
   TBranch        *b_TDCHits_channel;   //!
   TBranch        *b_TDCHits_TDC;   //!
   TBranch        *b_TDCHits_nHits;   //!
   TBranch        *b_TDCHits_width_wk;   //!
   TBranch        *b_TDCHits_leadTime1;   //!
   TBranch        *b_TDCHits_trailTime1;   //!
   TBranch        *b_TDCHits_leadTime2;   //!
   TBranch        *b_TDCHits_trailTime2;   //!
   TBranch        *b_TDCHits_leadTime3;   //!
   TBranch        *b_TDCHits_trailTime3;   //!
   TBranch        *b_TDCHits_leadTime4;   //!
   TBranch        *b_TDCHits_trailTime4;   //!
   TBranch        *b_TDCHits_spikesCtr;   //!
   TBranch        *b_merged_event_ADCHits_;   //!
   TBranch        *b_ADCHits_fUniqueID;   //!
   TBranch        *b_ADCHits_fBits;   //!
   TBranch        *b_ADCHits_channel;   //!
   TBranch        *b_ADCHits_ADC;   //!
   TBranch        *b_ADCHits_nHits;   //!
   TBranch        *b_ADCHits_samples;   //!
   TBranch        *b_ADCHits_dsp_sum;   //!
   TBranch        *b_ADCHits_dsp_mean;   //!
   TBranch        *b_ADCHits_dsp_cf_a;   //!
   TBranch        *b_ADCHits_dsp_cf_b;   //!
   TBranch        *b_ADCHits_dsp_cf_t;   //!
   TBranch        *b_ADCHits_localPtr;   //!
   TBranch        *b_merged_event_kMaxMult;   //!
   TBranch        *b_merged_event_kMaxChannelNr;   //!
   TBranch        *b_merged_event_subEvtId;   //!
   TBranch        *b_merged_event_errors_per_event;   //!
   TBranch        *b_merged_event_referenceChannel;   //!
   TBranch        *b_merged_event_referenceTime;   //!
   TBranch        *b_merged_event_totalNTDCHits;   //!
   TBranch        *b_merged_event_totalNADCHits;   //!

   mergedSelector(TTree * /*tree*/ =0) { }
   virtual ~mergedSelector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(mergedSelector,0);
};

#endif

#ifdef mergedSelector_cxx
void mergedSelector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_merged_event_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_merged_event_fBits);
   fChain->SetBranchAddress("TDCHits", &TDCHits_, &b_merged_event_TDCHits_);
   fChain->SetBranchAddress("TDCHits.fUniqueID", TDCHits_fUniqueID, &b_TDCHits_fUniqueID);
   fChain->SetBranchAddress("TDCHits.fBits", TDCHits_fBits, &b_TDCHits_fBits);
   fChain->SetBranchAddress("TDCHits.channel", TDCHits_channel, &b_TDCHits_channel);
   fChain->SetBranchAddress("TDCHits.TDC", TDCHits_TDC, &b_TDCHits_TDC);
   fChain->SetBranchAddress("TDCHits.nHits", TDCHits_nHits, &b_TDCHits_nHits);
   fChain->SetBranchAddress("TDCHits.width_wk", TDCHits_width_wk, &b_TDCHits_width_wk);
   fChain->SetBranchAddress("TDCHits.leadTime1", TDCHits_leadTime1, &b_TDCHits_leadTime1);
   fChain->SetBranchAddress("TDCHits.trailTime1", TDCHits_trailTime1, &b_TDCHits_trailTime1);
   fChain->SetBranchAddress("TDCHits.leadTime2", TDCHits_leadTime2, &b_TDCHits_leadTime2);
   fChain->SetBranchAddress("TDCHits.trailTime2", TDCHits_trailTime2, &b_TDCHits_trailTime2);
   fChain->SetBranchAddress("TDCHits.leadTime3", TDCHits_leadTime3, &b_TDCHits_leadTime3);
   fChain->SetBranchAddress("TDCHits.trailTime3", TDCHits_trailTime3, &b_TDCHits_trailTime3);
   fChain->SetBranchAddress("TDCHits.leadTime4", TDCHits_leadTime4, &b_TDCHits_leadTime4);
   fChain->SetBranchAddress("TDCHits.trailTime4", TDCHits_trailTime4, &b_TDCHits_trailTime4);
   fChain->SetBranchAddress("TDCHits.spikesCtr", TDCHits_spikesCtr, &b_TDCHits_spikesCtr);
   fChain->SetBranchAddress("ADCHits", &ADCHits_, &b_merged_event_ADCHits_);
   fChain->SetBranchAddress("ADCHits.fUniqueID", ADCHits_fUniqueID, &b_ADCHits_fUniqueID);
   fChain->SetBranchAddress("ADCHits.fBits", ADCHits_fBits, &b_ADCHits_fBits);
   fChain->SetBranchAddress("ADCHits.channel", ADCHits_channel, &b_ADCHits_channel);
   fChain->SetBranchAddress("ADCHits.ADC", ADCHits_ADC, &b_ADCHits_ADC);
   fChain->SetBranchAddress("ADCHits.nHits", ADCHits_nHits, &b_ADCHits_nHits);
   fChain->SetBranchAddress("ADCHits.samples[128]", ADCHits_samples, &b_ADCHits_samples);
   fChain->SetBranchAddress("ADCHits.dsp_sum", ADCHits_dsp_sum, &b_ADCHits_dsp_sum);
   fChain->SetBranchAddress("ADCHits.dsp_mean", ADCHits_dsp_mean, &b_ADCHits_dsp_mean);
   fChain->SetBranchAddress("ADCHits.dsp_cf_a", ADCHits_dsp_cf_a, &b_ADCHits_dsp_cf_a);
   fChain->SetBranchAddress("ADCHits.dsp_cf_b", ADCHits_dsp_cf_b, &b_ADCHits_dsp_cf_b);
   fChain->SetBranchAddress("ADCHits.dsp_cf_t", ADCHits_dsp_cf_t, &b_ADCHits_dsp_cf_t);
   fChain->SetBranchAddress("ADCHits.localPtr", ADCHits_localPtr, &b_ADCHits_localPtr);
   fChain->SetBranchAddress("kMaxMult", &kMaxMult, &b_merged_event_kMaxMult);
   fChain->SetBranchAddress("kMaxChannelNr", &kMaxChannelNr, &b_merged_event_kMaxChannelNr);
   fChain->SetBranchAddress("subEvtId", &subEvtId, &b_merged_event_subEvtId);
   fChain->SetBranchAddress("errors_per_event", &errors_per_event, &b_merged_event_errors_per_event);
   fChain->SetBranchAddress("referenceChannel", &referenceChannel, &b_merged_event_referenceChannel);
   fChain->SetBranchAddress("referenceTime", &referenceTime, &b_merged_event_referenceTime);
   fChain->SetBranchAddress("totalNTDCHits", &totalNTDCHits, &b_merged_event_totalNTDCHits);
   fChain->SetBranchAddress("totalNADCHits", &totalNADCHits, &b_merged_event_totalNADCHits);
}

Bool_t mergedSelector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef mergedSelector_cxx
