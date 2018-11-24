{

gSystem->Load("libGraf");
gSystem->Load("../Unpacker2/libUnpacker2.so");
printf("WARNING: UNPACKER2 LOADED\n"); 

gROOT->ProcessLine(".L calculate_times.cc+");
gROOT->ProcessLine(".L calculate_hits.cc+");
gROOT->ProcessLine(".L run_analysis.cc+");
//gROOT->ProcessLine(".L generate_diag_histo_panda.cc+");
gROOT->ProcessLine(".L pgenerate_diag_histo_panda.cc+");
printf("TRB3 Utilities loaded\n");

gStyle->SetPalette(1);
gStyle->SetOptFit(1111);
}
