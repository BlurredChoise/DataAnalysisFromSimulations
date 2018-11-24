//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Nov 18 12:16:32 2012 by ROOT version 5.33/03
// from TTree T/An example of a ROOT tree
// found on file: te12267004949.hld.root
//////////////////////////////////////////////////////////

#ifndef anastraws_h
#define anastraws_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxHits = 340;

class anastraws {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //Event           *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          EvtHdr_fUniqueID;
   UInt_t          EvtHdr_fBits;
   Int_t           EvtHdr_size;
   Int_t           EvtHdr_decoding;
   Int_t           EvtHdr_id;
   Int_t           EvtHdr_seqNr;
   Int_t           EvtHdr_date;
   Int_t           EvtHdr_time;
   Int_t           EvtHdr_year;
   Int_t           EvtHdr_month;
   Int_t           EvtHdr_day;
   Int_t           EvtHdr_hour;
   Int_t           EvtHdr_minute;
   Int_t           EvtHdr_second;
   Int_t           EvtHdr_pad;
   Int_t           EvtHdr_dataSize;
   Int_t           EvtHdr_paddedSize;
   Int_t           kMaxMult;
   Int_t           kMaxChannelNr;
   UInt_t          subEvtId;
   Int_t           errors_per_event;
   Int_t           referenceChannel;
   Int_t           referenceTime;
   Int_t           totalNTDCHits;
   Int_t           Hits_;
   UInt_t          Hits_fUniqueID[kMaxHits];   //[Hits_]
   UInt_t          Hits_fBits[kMaxHits];   //[Hits_]
   Int_t           Hits_channel[kMaxHits];   //[Hits_]
   Int_t           Hits_TDC[kMaxHits];   //[Hits_]
   Int_t           Hits_nHits[kMaxHits];   //[Hits_]
   Int_t           Hits_width_wk[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime1[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime1[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime2[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime2[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime3[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime3[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTime4[kMaxHits];   //[Hits_]
   Int_t           Hits_trailTime4[kMaxHits];   //[Hits_]
   Int_t           Hits_leadTimes[kMaxHits][100];   //[Hits_]
   Int_t           Hits_trailTimes[kMaxHits][100];   //[Hits_]
   Int_t           Hits_leadsNum[kMaxHits];   //[Hits_]
   Int_t           Hits_trailsNum[kMaxHits];   //[Hits_]
   Int_t           Hits_spikesCtr[kMaxHits];   //[Hits_]

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_totalNTDCHits;   //!
   TBranch        *b_event_Hits_;   //!
   TBranch        *b_Hits_fUniqueID;   //!
   TBranch        *b_Hits_fBits;   //!
   TBranch        *b_Hits_channel;   //!
   TBranch        *b_Hits_leadTimes;   //!
   TBranch        *b_Hits_trailTimes;   //!
   TBranch        *b_Hits_leadsNum;   //!
   TBranch        *b_Hits_trailsNum;   //!

   anastraws(TTree *tree=0);
   virtual ~anastraws();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef anastraws_cxx
anastraws::anastraws(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
//TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("te12267004949.hld.root");
TFile* f = new TFile("/home/shower/tools2/haha.root"); //RUN12

      if (!f || !f->IsOpen()) {
	// f = new TFile("1GeV/te12267004949.hld.root"); // 0.9 GeV/c 1750V mean 108
	// f = new TFile("1GeV/te12266235528.hld.root"); // 0.9 GeV/c 1800V mean 124
	//  f = new TFile("1GeV/te12267003239.hld.root"); // 0.9 GeV/c 1900V mean 150
	//   f = new TFile("1GeV/te12267010614.hld.root"); // 0.9 GeV/c 1700V mean 90
        // f = new TFile("te12265084234.hld.root"); // 2.0 GeV/c 1750V? mean 125/135 LI        
	// f = new TFile("2GeVHI/te12265194052.hld.root"); // 2.0 GeV/c  1800V mean 111/130
       //   f = new TFile("2GeVHI/te12265211154.hld.root"); // 2.0 GeV/c  1700V 85/95
       //te12336011300.hld.root_multihit_ref35"); //te12336011300.hld.root");
 //f = new TFile("/home/shower/te12336140923.hld.root"); //RUN1
 //f = new TFile("/home/shower/te12336152859.hld.root"); //RUN2
//f = new TFile("/home/shower/te12336193106.hld.root"); //RUN3
//f = new TFile("/home/shower/te12336201036.hld.root"); //RUN4
//f = new TFile("/home/shower/te12336205623.hld.root"); //RUN5
//f = new TFile("/home/shower/te12336215818.hld.root"); //RUN6
//f = new TFile("/home/shower/te12336225738.hld.root"); //RUN7
//f = new TFile("/home/shower/te12337143214.hld.root"); //RUN8
//f = new TFile("/home/shower/te12337154756.hld.root"); //RUN9  CORRUPTED
//f = new TFile("/home/shower/te12337162032.hld.root"); //RUN10
//RUN11 missing hld file on cerber
//f = new TFile("/home/shower/te12337173453.hld.root"); //RUN12
      }
      f->GetObject("T",tree);

   }
   Init(tree);
}

anastraws::~anastraws()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t anastraws::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t anastraws::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void anastraws::Init(TTree *tree)
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
   fChain->SetBranchAddress("totalNTDCHits", &totalNTDCHits, &b_event_totalNTDCHits);
   fChain->SetBranchAddress("TDCHits", &Hits_, &b_event_Hits_);
   fChain->SetBranchAddress("TDCHits.fUniqueID", Hits_fUniqueID, &b_Hits_fUniqueID);
   fChain->SetBranchAddress("TDCHits.fBits", Hits_fBits, &b_Hits_fBits);
   fChain->SetBranchAddress("TDCHits.channel", Hits_channel, &b_Hits_channel);
   fChain->SetBranchAddress("TDCHits.leadTimes[100]", Hits_leadTimes, &b_Hits_leadTimes);
   fChain->SetBranchAddress("TDCHits.trailTimes[100]", Hits_trailTimes, &b_Hits_trailTimes);
   fChain->SetBranchAddress("TDCHits.leadsNum", Hits_leadsNum, &b_Hits_leadsNum);
   fChain->SetBranchAddress("TDCHits.trailsNum", Hits_trailsNum, &b_Hits_trailsNum);
   Notify();
}

Bool_t anastraws::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void anastraws::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t anastraws::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef anastraws_cxx
