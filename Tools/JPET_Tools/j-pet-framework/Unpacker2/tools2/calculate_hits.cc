#include "../Unpacker2/EventIII.h"
#include "../Unpacker2/TDCHitIII.h"
#include "../Unpacker2/Event.h"
#include "../Unpacker2/TDCHit.h"
#include "../Unpacker2/TDCHitExtended.h"
#include "../Unpacker2/TDCChannel.h"
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TH2F.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>


#define CHANNELS_NUMBER 32

int calculate_hits(int eventsNum, const char* fileName, int referenceChannel)
{
  TChain chain("T");
  chain.Add(fileName);
    
  Event* pEvent = 0;
  TDCHitExtended* pHit = 0;
  TClonesArray* pArray = 0;
  chain.SetBranchAddress("event", &pEvent);

	string newFileName(fileName);
	newFileName = newFileName.substr(0, newFileName.size() - 5);
	newFileName += "_hits.root";

	TFile* new_file = new TFile(newFileName.c_str(), "RECREATE");
	TTree* new_tree = new TTree("T", "Times converted into hit units");
	EventIII* new_event = 0;
	Int_t split = 2;
	Int_t bsize = 64000;
	TBranch* event_branch =	new_tree->Branch("eventIII", "EventIII", &new_event, bsize, split);
  
  Int_t entries = (Int_t)chain.GetEntries();
  cout<<"Entries = " <<entries<<endl;

  double refTime = -100000;
  double actualLead = -100000;
  bool firstLeadFound = false;

  for(Int_t i = 0; i < entries; i++)
	{
    if (i % 10000 == 0) cerr<<i<<" of "<<entries<<"\r";
    if (i == eventsNum) break;
    chain.GetEntry(i);
    pArray = pEvent->GetTDCHitsArray();
    if (pArray == 0) continue;
    TIter iter(pArray);

   refTime = -100000;

    while( pHit = (TDCHitExtended*) iter.Next() )
		{
			TDCChannel* new_ch = new_event->AddTDCChannel(pHit->GetChannel());

			if (pHit->GetChannel() == referenceChannel) {
				refTime = pHit->GetAbsoluteTimeLine(0);
			}

			// hit construction logic
			actualLead = -100000;
			firstLeadFound = false;
//			cerr<<"Analysing channel "<<pHit->GetChannel()<<" with "<<pHit->GetTimeLineSize()<<" hits inside"<<endl;

			for (int j = 0; j < pHit->GetTimeLineSize(); j++) {
//				cerr<<"Getting hit nr"<<j<<endl;
				if (pHit->GetRisingEdge(j) == true && firstLeadFound == false) {
					actualLead = pHit->GetAbsoluteTimeLine(j);
					firstLeadFound = true;
//					cerr<<"Lead selected on channel "<<pHit->GetChannel()<<" as "<<j<<" with value ";
//					printf("%f\n", actualLead);
				}
				else if (pHit->GetRisingEdge(j) == false && firstLeadFound == true) {
					new_ch->AddHit(actualLead, pHit->GetAbsoluteTimeLine(j), refTime);
					firstLeadFound = false;
//					cerr<<"Trail selected on channel "<<pHit->GetChannel()<<" as "<<j<<" with value ";
//					printf("%f\n", pHit->GetAbsoluteTimeLine(j));
				}
			}
		}

		new_tree->Fill();
		new_event->Clear();
	}

	new_tree->Write();

	new_file->Close();

	return 0;
}
