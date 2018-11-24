#include "../Unpacker2/EventIII.h"
#include "../Unpacker2/TDCHitIII.h"
#include "../Unpacker2/Event.h"
#include "./calculate_times.cc"
#include "./calculate_hits.cc"
#include "./pgenerate_diag_histo_panda.cc"
#include "../Unpacker2/Unpacker2.h"
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TH2F.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>
#include <time.h>

int run_analysis(int eventsNum, char* fileName, char* confFile, int referenceChannel)
{
    clock_t tStart = clock();
  
	string newFileName(fileName);
	newFileName += ".root";

	Unpacker2(fileName, confFile, eventsNum);

	calculate_times(eventsNum, newFileName.c_str(), 49);

	newFileName = newFileName.substr(0, newFileName.size() - 5);
	newFileName += "_times.root";

	calculate_hits(eventsNum, newFileName.c_str(), referenceChannel);

	newFileName = newFileName.substr(0, newFileName.size() - 5);
	newFileName += "_hits.root";
	pgenerate_diag_histo_panda(eventsNum,newFileName.c_str() ,referenceChannel);

    	printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
