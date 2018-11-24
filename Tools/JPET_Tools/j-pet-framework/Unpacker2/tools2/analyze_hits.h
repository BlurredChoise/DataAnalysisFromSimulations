//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 16 13:39:15 2015 by ROOT version 5.34/25
// from TTree T/Times converted into hit units
// found on file: /home/guplab/hldFiles/xx15075103041.hld_times_hits.root
//////////////////////////////////////////////////////////

#ifndef analyze_hits_h
#define analyze_hits_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include "../Unpacker2/EventIII.h"
#include "/home/guplab/root/include/TObject.h"
#include "../Unpacker2/TDCChannel.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxTDCChannels = 22;

class analyze_hits : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
 //EventIII        *eventIII;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           totalNTDCChannels;
   Int_t           TDCChannels_;
   UInt_t          TDCChannels_fUniqueID[kMaxTDCChannels];   //[TDCChannels_]
   UInt_t          TDCChannels_fBits[kMaxTDCChannels];   //[TDCChannels_]
   Int_t           TDCChannels_channel[kMaxTDCChannels];   //[TDCChannels_]
   Double_t        TDCChannels_leadTime1[kMaxTDCChannels];   //[TDCChannels_]
   Double_t        TDCChannels_trailTime1[kMaxTDCChannels];   //[TDCChannels_]
   Double_t        TDCChannels_tot1[kMaxTDCChannels];   //[TDCChannels_]
   Double_t        TDCChannels_referenceDiff1[kMaxTDCChannels];   //[TDCChannels_]
   Double_t        TDCChannels_leadTimes[kMaxTDCChannels][100];   //[TDCChannels_]
   Double_t        TDCChannels_trailTimes[kMaxTDCChannels][100];   //[TDCChannels_]
   Double_t        TDCChannels_tots[kMaxTDCChannels][100];   //[TDCChannels_]
   Double_t        TDCChannels_referenceDiffs[kMaxTDCChannels][100];   //[TDCChannels_]
   Int_t           TDCChannels_hitsNum[kMaxTDCChannels];   //[TDCChannels_]

   // List of branches
   TBranch        *b_eventIII_fUniqueID;   //!
   TBranch        *b_eventIII_fBits;   //!
   TBranch        *b_eventIII_totalNTDCChannels;   //!
   TBranch        *b_eventIII_TDCChannels_;   //!
   TBranch        *b_TDCChannels_fUniqueID;   //!
   TBranch        *b_TDCChannels_fBits;   //!
   TBranch        *b_TDCChannels_channel;   //!
   TBranch        *b_TDCChannels_leadTime1;   //!
   TBranch        *b_TDCChannels_trailTime1;   //!
   TBranch        *b_TDCChannels_tot1;   //!
   TBranch        *b_TDCChannels_referenceDiff1;   //!
   TBranch        *b_TDCChannels_leadTimes;   //!
   TBranch        *b_TDCChannels_trailTimes;   //!
   TBranch        *b_TDCChannels_tots;   //!
   TBranch        *b_TDCChannels_referenceDiffs;   //!
   TBranch        *b_TDCChannels_hitsNum;   //!

   analyze_hits(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~analyze_hits() { }
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

   ClassDef(analyze_hits,0);
};

#endif

#ifdef analyze_hits_cxx
void analyze_hits::Init(TTree *tree)
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

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_eventIII_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_eventIII_fBits);
   fChain->SetBranchAddress("totalNTDCChannels", &totalNTDCChannels, &b_eventIII_totalNTDCChannels);
   fChain->SetBranchAddress("TDCChannels", &TDCChannels_, &b_eventIII_TDCChannels_);
   fChain->SetBranchAddress("TDCChannels.fUniqueID", TDCChannels_fUniqueID, &b_TDCChannels_fUniqueID);
   fChain->SetBranchAddress("TDCChannels.fBits", TDCChannels_fBits, &b_TDCChannels_fBits);
   fChain->SetBranchAddress("TDCChannels.channel", TDCChannels_channel, &b_TDCChannels_channel);
   fChain->SetBranchAddress("TDCChannels.leadTime1", TDCChannels_leadTime1, &b_TDCChannels_leadTime1);
   fChain->SetBranchAddress("TDCChannels.trailTime1", TDCChannels_trailTime1, &b_TDCChannels_trailTime1);
   fChain->SetBranchAddress("TDCChannels.tot1", TDCChannels_tot1, &b_TDCChannels_tot1);
   fChain->SetBranchAddress("TDCChannels.referenceDiff1", TDCChannels_referenceDiff1, &b_TDCChannels_referenceDiff1);
   fChain->SetBranchAddress("TDCChannels.leadTimes[100]", TDCChannels_leadTimes, &b_TDCChannels_leadTimes);
   fChain->SetBranchAddress("TDCChannels.trailTimes[100]", TDCChannels_trailTimes, &b_TDCChannels_trailTimes);
   fChain->SetBranchAddress("TDCChannels.tots[100]", TDCChannels_tots, &b_TDCChannels_tots);
   fChain->SetBranchAddress("TDCChannels.referenceDiffs[100]", TDCChannels_referenceDiffs, &b_TDCChannels_referenceDiffs);
   fChain->SetBranchAddress("TDCChannels.hitsNum", TDCChannels_hitsNum, &b_TDCChannels_hitsNum);
}

Bool_t analyze_hits::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef analyze_hits_cxx
