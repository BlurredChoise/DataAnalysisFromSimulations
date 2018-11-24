//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 12 15:04:48 2015 by ROOT version 5.34/25
// from TTree T/Times converted into hit units
// found on file: test_hits.root
//////////////////////////////////////////////////////////

#ifndef asd_h
#define asd_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include "./EventIII.h"
#include "/build/bellenot/source/root_v5.34.25/root/core/base/inc/TObject.h"
#include "./TDCChannel.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxTDCChannels = 10;

class asd : public TSelector {
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
   Int_t           TDCChannels_totalNTDCHits[kMaxTDCChannels];   //[TDCChannels_]
   Int_t           TDCChannels_channel[kMaxTDCChannels];   //[TDCChannels_]

   // List of branches
   TBranch        *b_eventIII_fUniqueID;   //!
   TBranch        *b_eventIII_fBits;   //!
   TBranch        *b_eventIII_totalNTDCChannels;   //!
   TBranch        *b_eventIII_TDCChannels_;   //!
   TBranch        *b_TDCChannels_fUniqueID;   //!
   TBranch        *b_TDCChannels_fBits;   //!
   TBranch        *b_TDCChannels_totalNTDCHits;   //!
   TBranch        *b_TDCChannels_channel;   //!

   asd(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~asd() { }
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

   ClassDef(asd,0);
};

#endif

#ifdef asd_cxx
void asd::Init(TTree *tree)
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
   fChain->SetBranchAddress("TDCChannels.totalNTDCHits", TDCChannels_totalNTDCHits, &b_TDCChannels_totalNTDCHits);
   fChain->SetBranchAddress("TDCChannels.channel", TDCChannels_channel, &b_TDCChannels_channel);
}

Bool_t asd::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef asd_cxx
