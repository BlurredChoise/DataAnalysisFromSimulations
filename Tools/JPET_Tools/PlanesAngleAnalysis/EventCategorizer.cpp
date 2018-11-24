/**
 *  @copyright Copyright 2017 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  @file EventCategorizer.cpp
 */

#include <iostream>
#include <JPetWriter/JPetWriter.h>
#include "EventCategorizer.h"
#include <TMath.h>
#include <TVector3.h>
//#include "FiltersStatistics.h"
#include <JPetOptionsTools/JPetOptionsTools.h>
using namespace jpet_options_tools;
using namespace std;

EventCategorizer::EventCategorizer(const char* name): JPetUserTask(name)
{
}

bool EventCategorizer::init()
{
 INFO( "Event categorization started." );

 fOutputEvents = new JPetTimeWindow( "JPetEvent" );

 fFiltersManager = new FiltersManager( getStatistics(), fParams );

 fFiltersManager->initFilters();

 getStatistics().createHistogram( new TH1F("DeltaPhiAngle", "DeltaPhiAngle", 721, 0, 180.0 ) );
 getStatistics().getHisto1D( "DeltaPhiAngle" )->GetXaxis()->SetTitle( "#varphi_{1} - #varphi_{2}" );
 getStatistics().getHisto1D( "DeltaPhiAngle" )->GetYaxis()->SetTitle( "Counts" );

 fIsUsedDataFromSimulation = isOptionSet( fParams.getOptions(), kIsUsedDataFromSimulationParamKey ) && getOptionAsBool( fParams.getOptions(), kIsUsedDataFromSimulationParamKey );


 return true;
}

bool EventCategorizer::exec()
{

  if ( auto timeWindow = dynamic_cast<const JPetTimeWindow* const>( fEvent ) ) 
  {
    uint n = timeWindow->getNumberOfEvents();

    for ( uint i = 0; i < n; ++i ) 
    {
      const JPetEvent& event = dynamic_cast<const JPetEvent&>( timeWindow->operator[]( i ) );
      AnalyzeThisEvent( event );     
    }
  } 
  else 
  {
    return false;
  }
  return true;
}

bool EventCategorizer::terminate()
{

  INFO("More than one hit Events done. Writing conrtrol histograms.");
  return true;
}

void EventCategorizer::saveEvents(const vector<JPetEvent>& events)
{
  for ( const auto& event : events )
    fOutputEvents->add<JPetEvent>( event );
}

void EventCategorizer::AnalyzeThisEvent(const JPetEvent& event)
{
 std::vector< AnalysisData > data;
 data.resize(event.getHits().size());

 for ( unsigned int i = 0; i < event.getHits().size(); ++i )
  data[ i ].fill( event.getHits().at( i ), event.getHits().at( 0 ), fIsUsedDataFromSimulation );

 if ( !fFiltersManager->isFiltrationPassed( data ) )
  return;

 int mother_gamma_for_3 = data[3].getMotherGammaIndex();
 int mother_gamma_for_4 = data[4].getMotherGammaIndex();

 if( !( ( mother_gamma_for_3 != mother_gamma_for_4 ) && ( mother_gamma_for_4 >= 0 ) && ( mother_gamma_for_3 >= 0 ) ) )
  return;

 TVector3 k1, k2, k3, k4;
 
 TVector3 kA = data[0].getHitPosition();
 TVector3 kB = data[1].getHitPosition();
 TVector3 kA2;
 TVector3 kB2;

 if ( mother_gamma_for_3 == 0 )
 {
  kA2 = data[2].getHitPosition();
  kB2 = data[3].getHitPosition();
 }
 else
 {
  kA2 = data[3].getHitPosition();
  kB2 = data[2].getHitPosition();
 }

 TVector3 polarization_A = kA.Cross( kA2 );
 TVector3 polarization_B = kB.Cross( kB2 );

 double delta_phi = polarization_A.Angle( polarization_B ) * TMath::RadToDeg();
 getStatistics().getHisto1D( "DeltaPhiAngle" )->Fill( delta_phi );
}

