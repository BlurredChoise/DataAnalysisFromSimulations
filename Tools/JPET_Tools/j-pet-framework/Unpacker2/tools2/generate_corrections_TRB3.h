//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 18 10:16:55 2013 by ROOT version 5.34/05
// from TTree T/Tree
// found on file: /tmp/xx13198153137.hld.root
//////////////////////////////////////////////////////////

#ifndef generate_corrections_TRB3_h
#define generate_corrections_TRB3_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include "../Unpacker2/Event.h"
#include <TObject.h>
#include "../Unpacker2/TDCHit.h"
#include "../Unpacker2/ADCHit.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxTDCHits = 1000;
const Int_t kMaxADCHits = 1;

class generate_corrections_TRB3 : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
 //Event           *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           totalNTDCHits;
   Int_t           totalNADCHits;
   Float_t         TDCReferenceTime;
   Int_t           TDCHits_;
   UInt_t          TDCHits_fUniqueID[kMaxTDCHits];   //[TDCHits_]
   UInt_t          TDCHits_fBits[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_channel[kMaxTDCHits];   //[TDCHits_]
   Float_t         TDCHits_leadFineTime1[kMaxTDCHits];   //[TDCHits_]
   Float_t         TDCHits_coarseTime1[kMaxTDCHits];   //[TDCHits_]
   Float_t         TDCHits_fineTimes[kMaxTDCHits][100];   //[TDCHits_]
   Float_t         TDCHits_coarseTimes[kMaxTDCHits][100];   //[TDCHits_]
   Float_t         TDCHits_leadTime1[kMaxTDCHits];   //[TDCHits_]
   Float_t         TDCHits_trailTime1[kMaxTDCHits];   //[TDCHits_]
   Float_t         TDCHits_leadTimes[kMaxTDCHits][100];   //[TDCHits_]
   Float_t         TDCHits_trailTimes[kMaxTDCHits][100];   //[TDCHits_]
   Int_t           TDCHits_leadsNum[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_trailsNum[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_finesNum[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_coarsesNum[kMaxTDCHits];   //[TDCHits_]
   Float_t         TDCHits_tot[kMaxTDCHits];   //[TDCHits_]
   Int_t           ADCHits_;
   UInt_t          ADCHits_fUniqueID[kMaxADCHits];   //[ADCHits_]
   UInt_t          ADCHits_fBits[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_channel[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_ADC[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_nHits[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_samples[kMaxADCHits][128];   //[ADCHits_]
   Int_t           ADCHits_dspSum[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_dspMean[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_dspCfA[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_dspCfB[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_dspCfT[kMaxADCHits];   //[ADCHits_]
   Int_t           ADCHits_localPtr[kMaxADCHits];   //[ADCHits_]

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_fBits;   //!
   TBranch        *b_event_totalNTDCHits;   //!
   TBranch        *b_event_totalNADCHits;   //!
   TBranch        *b_event_TDCReferenceTime;   //!
   TBranch        *b_event_TDCHits_;   //!
   TBranch        *b_TDCHits_fUniqueID;   //!
   TBranch        *b_TDCHits_fBits;   //!
   TBranch        *b_TDCHits_channel;   //!
   TBranch        *b_TDCHits_leadFineTime1;   //!
   TBranch        *b_TDCHits_coarseTime1;   //!
   TBranch        *b_TDCHits_fineTimes;   //!
   TBranch        *b_TDCHits_coarseTimes;   //!
   TBranch        *b_TDCHits_leadTime1;   //!
   TBranch        *b_TDCHits_trailTime1;   //!
   TBranch        *b_TDCHits_leadTimes;   //!
   TBranch        *b_TDCHits_trailTimes;   //!
   TBranch        *b_TDCHits_leadsNum;   //!
   TBranch        *b_TDCHits_trailsNum;   //!
   TBranch        *b_TDCHits_finesNum;   //!
   TBranch        *b_TDCHits_coarsesNum;   //!
   TBranch        *b_TDCHits_tot;   //!
   TBranch        *b_event_ADCHits_;   //!
   TBranch        *b_ADCHits_fUniqueID;   //!
   TBranch        *b_ADCHits_fBits;   //!
   TBranch        *b_ADCHits_channel;   //!
   TBranch        *b_ADCHits_ADC;   //!
   TBranch        *b_ADCHits_nHits;   //!
   TBranch        *b_ADCHits_samples;   //!
   TBranch        *b_ADCHits_dspSum;   //!
   TBranch        *b_ADCHits_dspMean;   //!
   TBranch        *b_ADCHits_dspCfA;   //!
   TBranch        *b_ADCHits_dspCfB;   //!
   TBranch        *b_ADCHits_dspCfT;   //!
   TBranch        *b_ADCHits_localPtr;   //!

   generate_corrections_TRB3(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~generate_corrections_TRB3() { }
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

   ClassDef(generate_corrections_TRB3,0);
};

#endif

#ifdef generate_corrections_TRB3_cxx
void generate_corrections_TRB3::Init(TTree *tree)
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

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_event_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_event_fBits);
   fChain->SetBranchAddress("totalNTDCHits", &totalNTDCHits, &b_event_totalNTDCHits);
   fChain->SetBranchAddress("totalNADCHits", &totalNADCHits, &b_event_totalNADCHits);
   fChain->SetBranchAddress("TDCReferenceTime", &TDCReferenceTime, &b_event_TDCReferenceTime);
   fChain->SetBranchAddress("TDCHits", &TDCHits_, &b_event_TDCHits_);
   fChain->SetBranchAddress("TDCHits.fUniqueID", TDCHits_fUniqueID, &b_TDCHits_fUniqueID);
   fChain->SetBranchAddress("TDCHits.fBits", TDCHits_fBits, &b_TDCHits_fBits);
   fChain->SetBranchAddress("TDCHits.channel", TDCHits_channel, &b_TDCHits_channel);
   fChain->SetBranchAddress("TDCHits.leadFineTime1", TDCHits_leadFineTime1, &b_TDCHits_leadFineTime1);
   fChain->SetBranchAddress("TDCHits.coarseTime1", TDCHits_coarseTime1, &b_TDCHits_coarseTime1);
   fChain->SetBranchAddress("TDCHits.fineTimes[100]", TDCHits_fineTimes, &b_TDCHits_fineTimes);
   fChain->SetBranchAddress("TDCHits.coarseTimes[100]", TDCHits_coarseTimes, &b_TDCHits_coarseTimes);
   fChain->SetBranchAddress("TDCHits.leadTime1", TDCHits_leadTime1, &b_TDCHits_leadTime1);
   fChain->SetBranchAddress("TDCHits.trailTime1", TDCHits_trailTime1, &b_TDCHits_trailTime1);
   fChain->SetBranchAddress("TDCHits.leadTimes[100]", TDCHits_leadTimes, &b_TDCHits_leadTimes);
   fChain->SetBranchAddress("TDCHits.trailTimes[100]", TDCHits_trailTimes, &b_TDCHits_trailTimes);
   fChain->SetBranchAddress("TDCHits.leadsNum", TDCHits_leadsNum, &b_TDCHits_leadsNum);
   fChain->SetBranchAddress("TDCHits.trailsNum", TDCHits_trailsNum, &b_TDCHits_trailsNum);
   fChain->SetBranchAddress("TDCHits.finesNum", TDCHits_finesNum, &b_TDCHits_finesNum);
   fChain->SetBranchAddress("TDCHits.coarsesNum", TDCHits_coarsesNum, &b_TDCHits_coarsesNum);
   fChain->SetBranchAddress("TDCHits.tot", TDCHits_tot, &b_TDCHits_tot);
   fChain->SetBranchAddress("ADCHits", &ADCHits_, &b_event_ADCHits_);
   fChain->SetBranchAddress("ADCHits.fUniqueID", &ADCHits_fUniqueID, &b_ADCHits_fUniqueID);
   fChain->SetBranchAddress("ADCHits.fBits", &ADCHits_fBits, &b_ADCHits_fBits);
   fChain->SetBranchAddress("ADCHits.channel", &ADCHits_channel, &b_ADCHits_channel);
   fChain->SetBranchAddress("ADCHits.ADC", &ADCHits_ADC, &b_ADCHits_ADC);
   fChain->SetBranchAddress("ADCHits.nHits", &ADCHits_nHits, &b_ADCHits_nHits);
   fChain->SetBranchAddress("ADCHits.samples[128]", &ADCHits_samples, &b_ADCHits_samples);
   fChain->SetBranchAddress("ADCHits.dspSum", &ADCHits_dspSum, &b_ADCHits_dspSum);
   fChain->SetBranchAddress("ADCHits.dspMean", &ADCHits_dspMean, &b_ADCHits_dspMean);
   fChain->SetBranchAddress("ADCHits.dspCfA", &ADCHits_dspCfA, &b_ADCHits_dspCfA);
   fChain->SetBranchAddress("ADCHits.dspCfB", &ADCHits_dspCfB, &b_ADCHits_dspCfB);
   fChain->SetBranchAddress("ADCHits.dspCfT", &ADCHits_dspCfT, &b_ADCHits_dspCfT);
   fChain->SetBranchAddress("ADCHits.localPtr", &ADCHits_localPtr, &b_ADCHits_localPtr);
}

Bool_t generate_corrections_TRB3::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef generate_corrections_TRB3_cxx
