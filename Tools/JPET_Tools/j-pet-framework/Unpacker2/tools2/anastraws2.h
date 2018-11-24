//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan  9 00:07:13 2013 by ROOT version 5.26/00
// from TTree T/Tree
// found on file: haha.root
//////////////////////////////////////////////////////////

#ifndef anastraws2_h
#define anastraws2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
   const Int_t kMaxTDCHits = 380;
   const Int_t kMaxADCHits = 1;

class anastraws2 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //Event           *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           totalNTDCHits;
   Int_t           totalNADCHits;
   Int_t           TDCHits_;
   UInt_t          TDCHits_fUniqueID[kMaxTDCHits];   //[TDCHits_]
   UInt_t          TDCHits_fBits[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_channel[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_leadTimes[kMaxTDCHits][100];   //[TDCHits_]
   Int_t           TDCHits_trailTimes[kMaxTDCHits][100];   //[TDCHits_]
   Int_t           TDCHits_leadsNum[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_trailsNum[kMaxTDCHits];   //[TDCHits_]
   Int_t           ADCHits_;
   UInt_t          ADCHits_fUniqueID[kMaxADCHits];   //[ADCHits_]
   UInt_t          ADCHits_fBits[kMaxADCHits];   //[ADCHits_]

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_fBits;   //!
   TBranch        *b_event_totalNTDCHits;   //!
   TBranch        *b_event_totalNADCHits;   //!
   TBranch        *b_event_TDCHits_;   //!
   TBranch        *b_TDCHits_fUniqueID;   //!
   TBranch        *b_TDCHits_fBits;   //!
   TBranch        *b_TDCHits_channel;   //!
   TBranch        *b_TDCHits_leadTimes;   //!
   TBranch        *b_TDCHits_trailTimes;   //!
   TBranch        *b_TDCHits_leadsNum;   //!
   TBranch        *b_TDCHits_trailsNum;   //!
   TBranch        *b_event_ADCHits_;   //!
   TBranch        *b_ADCHits_fUniqueID;   //!
   TBranch        *b_ADCHits_fBits;   //!

   anastraws2(TTree *tree=0);
   virtual ~anastraws2();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef anastraws2_cxx
anastraws2::anastraws2(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("haha.root");
      if (!f) {
         f = new TFile("haha.root");
      }
      tree = (TTree*)gDirectory->Get("T");

   }
   Init(tree);
}

anastraws2::~anastraws2()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t anastraws2::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t anastraws2::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void anastraws2::Init(TTree *tree)
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
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_event_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_event_fBits);
   fChain->SetBranchAddress("totalNTDCHits", &totalNTDCHits, &b_event_totalNTDCHits);
   fChain->SetBranchAddress("totalNADCHits", &totalNADCHits, &b_event_totalNADCHits);
   fChain->SetBranchAddress("TDCHits", &TDCHits_, &b_event_TDCHits_);
   fChain->SetBranchAddress("TDCHits.fUniqueID", TDCHits_fUniqueID, &b_TDCHits_fUniqueID);
   fChain->SetBranchAddress("TDCHits.fBits", TDCHits_fBits, &b_TDCHits_fBits);
   fChain->SetBranchAddress("TDCHits.channel", TDCHits_channel, &b_TDCHits_channel);
   fChain->SetBranchAddress("TDCHits.leadTimes[100]", TDCHits_leadTimes, &b_TDCHits_leadTimes);
   fChain->SetBranchAddress("TDCHits.trailTimes[100]", TDCHits_trailTimes, &b_TDCHits_trailTimes);
   fChain->SetBranchAddress("TDCHits.leadsNum", TDCHits_leadsNum, &b_TDCHits_leadsNum);
   fChain->SetBranchAddress("TDCHits.trailsNum", TDCHits_trailsNum, &b_TDCHits_trailsNum);
   fChain->SetBranchAddress("ADCHits", &ADCHits_, &b_event_ADCHits_);
   fChain->SetBranchAddress("ADCHits.fUniqueID", &ADCHits_fUniqueID, &b_ADCHits_fUniqueID);
   fChain->SetBranchAddress("ADCHits.fBits", &ADCHits_fBits, &b_ADCHits_fBits);
   Notify();
}

Bool_t anastraws2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void anastraws2::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t anastraws2::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef anastraws2_cxx
