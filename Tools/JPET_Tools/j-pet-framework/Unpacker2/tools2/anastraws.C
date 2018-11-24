#define anastraws_cxx
#include "anastraws.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void anastraws::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L anastraws.C
//      Root > anastraws t
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

   // histograms
   TH1F *test = new TH1F("test","drif time test",11000,0.,22000.);
   TH2F *drift_all = new TH2F("drift_all","drift time all channels",300,-0.,300.,32,0,31);
   TH2F *ttot = new TH2F("ttot","tot all channels",400,0.,400.,32,0,31);
   TH1F *multh = new TH1F("multh","hit multiplicity",6,0,6);
   TH1F *channel = new TH1F("channel","channel number",32,0,32);
   TH1F *mults = new TH1F("mults","mult straws",32,0,32);   
   TH2F *drift_tot = new TH2F("drift_tot","drift time vs TOT",1400,-1000.,400.,500,0.,500.);
   //TH2F *drift_tot = new TH2F("drift_tot","drift time vs TOT",3000,-1500.,1500.,500,0.,500.);
   TH2F *drift_tot1 = new TH2F("drift_tot1","drift time vs TOT",300,0.,300.,500,0.,500.);
   TH2F *drift_tot2 = new TH2F("drift_tot2","drift time vs TOT",300,0.,300.,500,0.,500.);
   TH2F *drift_cros1 = new TH2F("drift_cros1","drift time vs drift +1",300,0.,300.,300,0.,300.);
   TH2F *drift_cros2 = new TH2F("drift_cros2","drift time vs drift +2",300,0.,300.,300,0.,300.);
   TH1F *tottm30 = new TH1F("tottm30","tot trunc.mean30",300,0,300);
   TH1F *refTime = new TH1F("refTime", "ref time", 3200, 0, 3200);
   TH2F *drift_tot_l1 = new TH2F("drift_tot_l1","drift time vs TOT layer1",300,0.,300.,300,0.,300.);
   TH2F *drift_tot_l2 = new TH2F("drift_tot_l2","drift time vs TOT layer2",300,0.,300.,300,0.,300.);
   TH1F *structure_channels = new TH1F("structure_channels", "Channels in the structure", 32, 0, 32);
   TH2F *drift_all_raw = new TH2F("drift_all_raw","raw drift time all channels",3000,-1500.,1500.,32,0,31);
   TH2F *drift_tot_raw = new TH2F("drift_tot_raw","raw drift time vs tot all channels",3000,-1500.,1500.,500,0,500);
   TH2F *drift_tot_rejected_trg = new TH2F("drift_tot_rejected_trg","raw drift time vs tot all channels on rejected triggers",3000,-1500.,1500.,500,0,500);
   TH2F *drift_tot_ch[32]; // = new TH2F("drift_tot","drift time vs TOT",300,0.,300.,300,0.,300.);
   TH1F *drift_ch[32];
   
   for(int i = 0; i < 32; i++) {
    drift_tot_ch[i] = new TH2F(Form("drift_tot_ch_%d", i), Form("Individual tot vs drift channel %d", i), 300, 0, 300, 300, 0, 300);
    drift_ch[i] = new TH1F(Form("drift_ch_%d", i), Form("Individual drift channel %d", i), 300, 0, 300);
    //drift_tot_ch[i] = new TH2F(Form("drift_tot_ch_%d", i), Form("Individual tot vs drift channel %d", i), 3000, -1500, 1500, 300, 0, 300); 
   }

   Long64_t nentries = fChain->GetEntriesFast();
   nentries=1000000;
   Float_t t_offset[32]={2497.0, 2495.0, 2495.0, 2498.0, 2495.0, 0.0, 2497.0, 2497.0, 2493.0, 2496.0, 2495.0, 2495.0, 2493.0, 2493.0, 2490.0, 2496.0, 2494.0, 0.0, 2493.0, 2496.0, 0.0, 2495.0, 2494.0, 2496.0, 2495.0, 2493.0, 2495.0, 2494.0, 2493.0, 0.0, 0.0, 0.0};
   Float_t tt_offset[32]={0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
0.0, 0.0, 0.0, 0., 22., -5., -13., 3., -2., -5.,
0.0, 0.0, 0.0, 0., 0.,   0.,0.0 , -8., 0.,  0., 
			 0., 0.};
   Float_t tdrift_golden[32];
   Float_t ttot_golden[32];
   Long64_t nbytes = 0, nb = 0;
   
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry%1000 == 0) {cerr<<jentry<<endl; }
      
      Long64_t ientry = LoadTree(jentry);
      
      if (ientry < 0) 
	break;
      cerr<<"crap"<<endl;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;
      cerr<<"crap2"<<endl;
//       refTime->Fill(0.1 * referenceTime);
//       
//       //if (0.1*referenceTime < 890 || 0.1*referenceTime > 940)
//       if (0.1*referenceTime < 2910 || 0.1*referenceTime > 2950)
// 	continue;
//       
//       Int_t muls=0;
//       
//       for( Int_t i=0;i<32;i++) {
// 	tdrift_golden[i]=0.0;
// 	ttot_golden[i]=0.0;
//       }
//       
//       
//       bool reject_event = false;
//       
//       // check for trigger multiplicty rejection
// //       for (Int_t e_hits=0; e_hits<totalNHits; e_hits++) {
// // 	    if (Hits_channel[e_hits] == 63 && Hits_leadsNum[e_hits] > 1) {
// // 	      reject_event = true;
// // 	    }      
// //       }
// 	
       for (Int_t e_hits=0; e_hits<totalNTDCHits; e_hits++) {
 	if(Hits_channel[e_hits]>28)
 	  continue;
// 	
// 	Float_t tdrift=1000.;
// 	Float_t tdrift_m=1000.0;
// 	Int_t mulh=0; 
 	Float_t tot=0.0;
// 	
	for (Int_t c_hits=0; c_hits<Hits_leadsNum[e_hits]; c_hits++) {
//       
// 	  test->Fill(0.1 * (Hits_leadTimes[e_hits][c_hits] - referenceTime));
// 	  tdrift = 0.1*(Hits_leadTimes[e_hits][c_hits] - referenceTime) + (3000 -t_offset[Hits_channel[e_hits]]);
// 	  
// 	  if (reject_event == false) {
// 	      drift_all_raw->Fill(tdrift, Hits_channel[e_hits]);
// 	      drift_tot_raw->Fill(tdrift, (0.1 * (-Hits_leadTimes[e_hits][c_hits] + Hits_trailTimes[e_hits][c_hits])));
// 	      
// 	      drift_tot_ch[Hits_channel[e_hits]]->Fill(0.1*(Hits_leadTimes[e_hits][c_hits] - referenceTime) + (3000 -t_offset[Hits_channel[e_hits]]), (0.1 * (-Hits_leadTimes[e_hits][c_hits] + Hits_trailTimes[e_hits][c_hits])));
// 
// 	      drift_ch[Hits_channel[e_hits]]->Fill(0.1*(Hits_leadTimes[e_hits][c_hits] - referenceTime) + (3000 -t_offset[Hits_channel[e_hits]]));
// 	      
// 	      if(tdrift < 300) {
// 	      //if(tdrift > -1200 && tdrift < -950) {
// 		mulh++;
// 		
// 		if(tdrift < tdrift_m) {
// 		  tdrift_m = tdrift;
 		  tot = 0.1*(-Hits_leadTimes[e_hits][c_hits] + Hits_trailTimes[e_hits][c_hits]); //-tt_offset[Hits_channel[e_hits]];
// 		}
// 	      }
// 	  }
// 	  else {
// 	    drift_tot_rejected_trg->Fill(0.1*(Hits_leadTimes[e_hits][c_hits] - referenceTime) + (3000 -t_offset[Hits_channel[e_hits]]), (0.1 * (-Hits_leadTimes[e_hits][c_hits] + Hits_trailTimes[e_hits][c_hits])));
// 	  }
// 	  
// 	}        
// 	if(tdrift_m < 1000.0 && reject_event == false) { 
// 	      channel->Fill(Hits_channel[e_hits]);
// 	      drift_all->Fill(tdrift_m, Hits_channel[e_hits]);
// 	      multh->Fill(mulh);
 	      ttot->Fill(tot,Hits_channel[e_hits]);

	}}
	      // 	      muls++;
// 	      if(mulh == 1) {
// 		tdrift_golden[Hits_channel[e_hits]]=tdrift_m;
// 		ttot_golden[Hits_channel[e_hits]]=tot;
// 	      }
// //  	      if (tdrift_m > 190) {
// //  		reject_event =true;
// //  	      }
// 	}
// 	       //cout<<"tdrift=="<<tdrift<<"channel=="<<Hits_channel[e_hits]<<endl;
//       }
//       
// //       if ( ( (tdrift_golden[0]>0.0) && (tdrift_golden[1]>0.0) && (TMath::Abs(tdrift_golden[0] - tdrift_golden[1]) > 50) ) || ( (tdrift_golden[27]>0.0) && (tdrift_golden[28]>0.0) && (TMath::Abs(tdrift_golden[27] - tdrift_golden[28]) > 50) ) ) {
// // 	reject_event = true;
// //       }
// //       
// //        if (reject_event) {
// //  	continue;
// //        }
//                mults->Fill(muls);
//          Float_t tot_cal=0.0;Float_t tot_tm30=0.0;
//          Int_t multm=0;
//          if (muls>13) {
// 	  
// 	   for (Int_t j=0;j<28;j++) {
// 	    
// 	   if(tdrift_golden[j]>0.0 && ttot_golden[j]>0) {                                       
// 	      
// 	      drift_tot->Fill(tdrift_golden[j],ttot_golden[j]);
// 	      drift_tot_ch[j]->Fill(tdrift_golden[j],ttot_golden[j]);
// 	      
// 	      if(tdrift_golden[j] > 190) {
// 		  structure_channels->Fill(j);
// 	      }
// 	      
// 	      if(j%2 == 0) {
// 		drift_tot_l1->Fill(tdrift_golden[j],ttot_golden[j]);
// 	      }
// 	      else {
// 		drift_tot_l2->Fill(tdrift_golden[j],ttot_golden[j]);
// 	      }
// 	      
//               if(tdrift_golden[j+1]>0) {
// 		
//                 drift_cros1->Fill(tdrift_golden[j],tdrift_golden[j+1]);
//                 drift_tot1->Fill(tdrift_golden[j],ttot_golden[j]);
// 	      }
//                 
//                if(tdrift_golden[j+2]>0 && tdrift_golden[j+1]==0 && tdrift_golden[j-1]==0) { 
// 		//if (tdrift_golden[j]>80 && tdrift_golden[j]<280) 
// 		 //   tot_cal=ttot_golden[j]-(258.0 -1.193*tdrift_golden[j]+0.0027*pow(tdrift_golden[j],2))+185;//1900 V
// 	       //     tot_cal=ttot_golden[j]-(251.0 -1.29*tdrift_golden[j]+0.0027*pow(tdrift_golden[j],2))+170; //1800 V
//       	 	//tot_cal=ttot_golden[j]-(243.2 -1.39*tdrift_golden[j]+0.0023*pow(tdrift_golden[j],2))+150;//1700 V
//                  drift_cros2->Fill(tdrift_golden[j],tdrift_golden[j+2]);
//                  drift_tot2->Fill(tdrift_golden[j],ttot_golden[j]);//tot_cal);  
//                  if(tot_cal<175.) {
// 		   tot_tm30=tot_tm30+tot_cal;multm++;
// 		 }						
// 	       }          
// 	    }
// 	  }
//           if(multm>5) {
//                tot_tm30=tot_tm30/multm;
//                tottm30->Fill(tot_tm30);
// 	  }  
//           //mults->Fill(multm);  
//          }
   }
}
