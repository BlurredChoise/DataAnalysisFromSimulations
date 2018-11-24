/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
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
 *  @file JPetGATEParser.cpp
 */

#include <iostream>
#include <JPetWriter/JPetWriter.h>
#include <JPetAnalysisTools/JPetAnalysisTools.h>
#include <JPetOptionsTools/JPetOptionsTools.h>
#include <JPetGATEParser/JPetGATEParser.h>
#include <JPetGATEParser/JPetGATEParserTools.h>
#include <JPetGATEEvent/JPetGATEEvent.h>
#include <JPetGATETrack/JPetGATETrack.h>
#include <JPetGATETrackInteraction/JPetGATETrackInteraction.h>

#include <TRandom3.h>
#include <string>
#include <TMath.h>
#include <cmath>
#include <array>

using namespace jpet_options_tools;

JPetGATEParser::JPetGATEParser(const char* name) : JPetUserTask(name) { }

JPetGATEParser::~JPetGATEParser() { }


bool JPetGATEParser::init()
{
  // create detector map
  JPetGATEParserTools::printSci( getParamBank() );
  std::unique_ptr<JPetGeomMapping> fDetectorMap(new JPetGeomMapping(getParamBank()));
  fOutputEvents = new JPetTimeWindowMC("JPetHit", "JPetMCHit", "JPetMCDecayTree");
  auto opts = getOptions();

  if (isOptionSet(fParams.getOptions(), kMaxTimeWindowParamKey)) {
    fMaxTime = getOptionAsDouble(fParams.getOptions(), kMaxTimeWindowParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kMinTimeWindowParamKey)) {
    fMinTime = getOptionAsDouble(fParams.getOptions(), kMinTimeWindowParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kSourceActivityParamKey)) {
    fSimulatedActivity = getOptionAsDouble(fParams.getOptions(), kSourceActivityParamKey);
  }

  if (isOptionSet(fParams.getOptions(), kZresolutionParamKey)) {
    fZresolution = getOptionAsDouble(fParams.getOptions(), kZresolutionParamKey);
  }
  if (isOptionSet(fParams.getOptions(), kEnergyThresholdParamKey)) {
    fExperimentalThreshold = getOptionAsDouble(fParams.getOptions(), kEnergyThresholdParamKey);
  }
  INFO("MC Hit wrapper started.");

  return true;
}


bool JPetGATEParser::exec()
{
  if (auto& mcEventPack = dynamic_cast<JPetGATEEvent* const>(fEvent)) {

    processMCEvent(mcEventPack);

    if ( fActivityIndex > abs( fMinTime * fSimulatedActivity * pow( 10, -6 ) ) )
    {
      saveHits();
      fActivityIndex = 0;
    } 
    else 
    {
      fActivityIndex++;
    }

  } else {
    return false;
  }

  return true;
}


bool JPetGATEParser::terminate()
{
  /*INFO( "TERMINATE" );
  unsigned int n = fSci.size();
  INFO( n );
  for ( unsigned int i = 0; i < n; ++ i )
  {
   INFO( "******" );
   INFO( fSci[ i ].x() );
   INFO( fSci[ i ].y() );
   INFO( fSci[ i ].z() );
  }*/

  INFO("MC events processing ended");
  return true;
}


void JPetGATEParser::processMCEvent(JPetGATEEvent* event)
{
  // first adjust all hits in single event to time window scheme
  std::unique_ptr<TRandom3> random(new TRandom3(0));
  float timeShift = random->Uniform(fMinTime, fMaxTime);

  for ( std::vector<JPetGATETrack>::iterator track_it = event->fTracks.begin(); track_it != event->fTracks.end(); ++track_it )
  {
   for ( std::vector<JPetGATETrackInteraction>::iterator interaction_it = track_it->fTrackInteractions.begin(); interaction_it != track_it->fTrackInteractions.end(); ++interaction_it )
   {
     JPetMCHit mcHit = JPetGATEParserTools::createJPetMCHit( *interaction_it, getParamBank() );
     //tryAddSci( (*interaction_it).getScintilatorPosition() );
     fStoredMCHits.push_back(mcHit);

     JPetHit  recHit =  JPetGATEParserTools::reconstructHit(mcHit, timeShift, fZresolution);

     if ( JPetGATEParserTools::isHitReconstructed( recHit, fExperimentalThreshold ) )
     {
      fStoredHits.push_back(recHit);
     }
   }
  }
}

void JPetGATEParser::saveHits()
{
 // INFO( "fStoredHits" );
//  INFO( fStoredHits.size() );

 // INFO( "fStoredMCHits" );
 // INFO( fStoredMCHits.size() );

  for ( const auto& hit : fStoredHits ) {
    fOutputEvents->add<JPetHit>( hit );
  }

  for (const auto& mcHit : fStoredMCHits) {
    dynamic_cast<JPetTimeWindowMC*>(fOutputEvents)->addMCHit<JPetMCHit>(mcHit);
  }

  fStoredMCHits.clear();
  fStoredHits.clear();
}

void JPetGATEParser::tryAddSci( const TVector3& s )
{
 unsigned int n = fSci.size();
 for ( unsigned int i = 0; i < n; ++i )
 {
  if ( fSci[ i ] == s )
   return;
 }
 INFO( "Adding new " );
 INFO( s.x() );
 INFO( s.y() );
 INFO( s.z() );
 fSci.push_back( s );
}

