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
 *  @file JPetGATEParser.h
 */

#ifndef JPETGATEPARSER_H
#define JPETGATEPARSER_H

#include <map>
#include <vector>
#include <JPetUserTask/JPetUserTask.h>
#include <JPetMCHit/JPetMCHit.h>
#include <JPetHit/JPetHit.h>
#include <JPetMCDecayTree/JPetMCDecayTree.h>
#include <JPetGeomMapping/JPetGeomMapping.h>
#include <JPetGATEEvent/JPetGATEEvent.h>
#include <TVector3.h>

class JPetWriter;

#ifdef __CINT__
//when cint is used instead of compiler, override word is not recognized
//nevertheless it's needed for checking if the structure of project is correct
#   define override
#endif

/**
 * @brief      Module responsible for creating JPetMCHit from GATE MC simulations
 *
 */
class JPetGATEParser: public JPetUserTask
{

public:
  JPetGATEParser(const char* name);
  virtual ~JPetGATEParser();
  virtual bool init() override;
  virtual bool exec() override;
  virtual bool terminate() override;


protected :
  JPetGeomMapping* fDetectorMap;

  double fMaxTime = 0.;
  double fMinTime = -50.e6; // electronic time window 50 micro seconds - true for run 3
  double fSimulatedActivity = 4.7; //< in MBq; value for run3

  float fZresolution = 0.976; // 80ps   12.2  velocity
  double fExperimentalThreshold = 10; //< in keV

  // constants for histograms
  int kEffiHisto_ene_nBin = 200;
  double kEffiHisto_ene_width = 8;

  int kEffiMap_nSlice = 81;
  float kEffiMap_width = 0.5; // cm  -20:20

  // internal variables
  const std::string kMaxTimeWindowParamKey = "GATEParser_MaxTimeWindow_double";
  const std::string kMinTimeWindowParamKey = "GATEParser_MinTimeWindow_double";
  const std::string kSourceActivityParamKey = "GATEParser_SourceActivity_double";
  const std::string kMakeHistogramsParamKey = "GATEParser_MakeHistograms_bool";
  const std::string kMakeEfficienciesParamKey = "GATEParser_MakeEfficiencies_bool";
  const std::string kZresolutionParamKey = "GATEParser_Zresolution_double";
  const std::string kEnergyThresholdParamKey = "GATEParser_EnergyThreshold_double";

  long fActivityIndex = 0;

  std::vector<JPetMCHit> fStoredMCHits; ///< save MC hits into single time window when it contains enought hits
  std::vector<JPetHit> fStoredHits; ///< save RECONSTRUCTED MC hits into single time window when it contains enought hits

  void processMCEvent(JPetGATEEvent*);
  void saveHits();

  std::vector<TVector3> fSci;
  void tryAddSci( const TVector3& s );

};

#endif
