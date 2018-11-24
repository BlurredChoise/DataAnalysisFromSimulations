#include "FilterTOTRange.h"

FilterTOTRange::FilterTOTRange( JPetStatistics& stats, JPetParams& params ) : Filter( stats, params )
{
 setName( "FilterTOTRange" );
}

FilterTOTRange::~FilterTOTRange()
{
}

FilterTOTRange::HistTOTData FilterTOTRange::HistTOTData::getHTD( std::string hnb, std::string hna, double tot,  std::string hnb2, std::string hna2, int sciID )
{
 FilterTOTRange::HistTOTData htd;
 htd.kHistogramNameBefore = hnb;
 htd.kHistogramNameAfter = hna;
 htd.fTOT = tot;
 htd.kHistogramNameBefore2D = hnb2;
 htd.kHistogramNameAfter2D = hna2;
 htd.fSciID = sciID;
 return htd;
}

bool FilterTOTRange::initStatistics()
{
 if ( !setIndexForFilter( kFilterIndexParamKey ) )
  return false;
 if ( !fillUnsignedIntParameter( kFilterCheckFirstNHitsParamKey, kFilterCheckFirstNHits ) )
  return false;
 if ( !fillDoubleParameter( kFilterTOTMinimumValueParamKey, kFilterTOTMinimumValue ) )
  return false;
 if ( !fillDoubleParameter( kFilterTOTMaximumValueParamKey, kFilterTOTMaximumValue ) )
  return false;

 kDataFromSimulation = getBoolParamValue( kFilterDataFromSimulationParamKey );
 coutLine();
 std::cout << getName() << " index = " << getIndex() << std::endl;
 std::cout << "kFilterTOTMinimumValue = " << kFilterTOTMinimumValue << std::endl;
 std::cout << "kFilterTOTMaximumValue = " << kFilterTOTMaximumValue << std::endl;
 coutLine();

 if ( kDataFromSimulation )
 {
 add1DHists( kH1TOTAllBefore, kH1TOTAllAfter, 2000, -1, 2000, "E_{dep} [keV]", "Counts" );
 add2DHists( kH2TOTAllBefore, kH2TOTAllAfter, 2000, -1, 2000, 804,-1, 200, "E_{dep} [keV]", "Scintilator ID" );
 }
 else
 {
 add1DHists( kH1TOTAllBefore, kH1TOTAllAfter, 404, -1, 100, "TOT [ns]", "Counts" );
 add2DHists( kH2TOTAllBefore, kH2TOTAllAfter, 404, -1, 100, 804,-1, 200, "TOT [ns]", "Scintilator ID" );
 }

 fHistNameVsTOT.resize(kFilterCheckFirstNHits);

 if ( kFilterCheckFirstNHits >= 4 )
 {
  if ( kDataFromSimulation ) 
  {
   add1DHists( kH1TOTNo4Before, kH1TOTNo4After, 2000, -1, 2000, "E_{dep} [keV]", "Counts" ); 
   add2DHists( kH2TOTNo4Before, kH2TOTNo4After, 2000, -1, 2000, 804,-1, 200, "E_{dep} [keV]", "Scintilator ID" );
  }
  else
  {
   add1DHists( kH1TOTNo4Before, kH1TOTNo4After, 404, -1, 100, "TOT [ns]", "Counts" ); 
   add2DHists( kH2TOTNo4Before, kH2TOTNo4After, 404, -1, 100, 804,-1, 200, "TOT [ns]", "Scintilator ID" );
  }
  fHistNameVsTOT[3] = FilterTOTRange::HistTOTData::getHTD( kH1TOTNo4Before, kH1TOTNo4After, 0, kH2TOTNo4Before, kH2TOTNo4After, -1 );
 }

 if ( kFilterCheckFirstNHits >= 3 )
 {
  if ( kDataFromSimulation ) 
  {
   add1DHists( kH1TOTNo3Before, kH1TOTNo3After, 2000, -1, 2000, "E_{dep} [keV]", "Counts" ); 
   add2DHists( kH2TOTNo3Before, kH2TOTNo3After, 2000, -1, 2000, 804,-1, 200, "E_{dep} [keV]", "Scintilator ID" );
  }
  else
  {
   add1DHists( kH1TOTNo3Before, kH1TOTNo3After, 404, -1, 100, "TOT [ns]", "Counts" );
   add2DHists( kH2TOTNo3Before, kH2TOTNo3After, 404, -1, 100, 804,-1, 200, "TOT [ns]", "Scintilator ID" );
  }
  fHistNameVsTOT[2] = FilterTOTRange::HistTOTData::getHTD( kH1TOTNo3Before, kH1TOTNo3After, 0, kH2TOTNo3Before, kH2TOTNo3After, -1 );
 }

 if ( kFilterCheckFirstNHits >= 2 )
 {
    if ( kDataFromSimulation ) 
  {
   add1DHists( kH1TOTNo2Before, kH1TOTNo2After, 2000, -1, 2000, "E_{dep} [keV]", "Counts" ); 
   add2DHists( kH2TOTNo2Before, kH2TOTNo2After, 2000, -1, 2000, 804,-1, 200, "E_{dep} [keV]", "Scintilator ID" );
  }
  else
  {
   add1DHists( kH1TOTNo2Before, kH1TOTNo2After, 404, -1, 100, "TOT [ns]", "Counts" );
   add2DHists( kH2TOTNo2Before, kH2TOTNo2After, 404, -1, 100, 804,-1, 200, "TOT [ns]", "Scintilator ID" );
  }
  fHistNameVsTOT[1] = FilterTOTRange::HistTOTData::getHTD( kH1TOTNo2Before, kH1TOTNo2After, 0, kH2TOTNo2Before, kH2TOTNo2After, -1 );
 }

 if ( kFilterCheckFirstNHits >= 1 )
 {
  if ( kDataFromSimulation ) 
  {
   add1DHists( kH1TOTNo1Before, kH1TOTNo1After, 2000, -1, 2000, "E_{dep} [keV]", "Counts" ); 
   add2DHists( kH2TOTNo1Before, kH2TOTNo1After, 2000, -1, 2000, 804,-1, 200, "E_{dep} [keV]", "Scintilator ID" );
  }
  else
  {
   add1DHists( kH1TOTNo1Before, kH1TOTNo1After, 404, -1, 100, "TOT [ns]", "Counts" );
   add2DHists( kH2TOTNo1Before, kH2TOTNo1After, 404, -1, 100, 804,-1, 200, "TOT [ns]", "Scintilator ID" );
  }
  fHistNameVsTOT[0] = FilterTOTRange::HistTOTData::getHTD( kH1TOTNo1Before, kH1TOTNo1After, 0, kH2TOTNo1Before, kH2TOTNo1After, -1 );
 }

 return true;
}

bool FilterTOTRange::filterData( std::vector<AnalysisData>& data ) 
{
 if ( data.size() < kFilterCheckFirstNHits )
  return false;

 bool passed = true;
 double TOT = 0;

 for ( unsigned int i = 0; i < kFilterCheckFirstNHits; ++i )
 {
  if ( kDataFromSimulation )
   TOT = data[i].getEnergyDeposition();
  else
   TOT = data[i].getTOT();

  passed = passed && ( TOT > kFilterTOTMinimumValue ) && ( TOT < kFilterTOTMaximumValue );
  fHistNameVsTOT[i].fTOT = TOT;
  fHistNameVsTOT[i].fSciID = data[i].getScintilatorID();
 }

 for ( unsigned int i = 0; i < kFilterCheckFirstNHits; ++i )
 {
  noticeFor1DHists( fHistNameVsTOT[i].kHistogramNameBefore, fHistNameVsTOT[i].kHistogramNameAfter, passed, fHistNameVsTOT[i].fTOT );
  noticeFor1DHists( kH1TOTAllBefore, kH1TOTAllAfter, passed, fHistNameVsTOT[i].fTOT );
  noticeFor2DHists( fHistNameVsTOT[i].kHistogramNameBefore2D, fHistNameVsTOT[i].kHistogramNameAfter2D, passed, fHistNameVsTOT[i].fTOT, fHistNameVsTOT[i].fSciID );
  noticeFor2DHists( kH2TOTAllBefore, kH2TOTAllAfter, passed, fHistNameVsTOT[i].fTOT, fHistNameVsTOT[i].fSciID );
 }

 return !passed;
}


