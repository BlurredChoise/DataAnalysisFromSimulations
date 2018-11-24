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
 *  @file EventCategorizer.h
 */

#ifndef EVENTCATEGORIZER_H
#define EVENTCATEGORIZER_H

#include <vector>
#include <JPetUserTask/JPetUserTask.h>
#include <JPetHit/JPetHit.h>
#include <JPetEvent/JPetEvent.h>
#include "TVector3.h"
//#include "FiltersStatistics.h"
#include "AnalysisData.h"
#include "FiltersManager.h"
#include <string>

class JPetWriter;

#ifdef __CINT__
#	define override
#endif

class EventCategorizer : public JPetUserTask{
public:
	EventCategorizer(const char * name);
	virtual ~EventCategorizer(){}
	virtual bool init() override;
	virtual bool exec() override;
	virtual bool terminate() override;

protected:
	void saveEvents(const std::vector<JPetEvent>& event);
	bool fSaveControlHistos = true;
private:
	void AnalyzeThisEvent(const JPetEvent& event);
	//Return true if theta is in theta limit regime
	bool TryCalculatePhi(AnalysisData& ad1, AnalysisData& ad2, double& phi);
    //FiltersStatistics* fFiltersStatistics;
	const std::string kHitsPerEventParamKey = "EventCategorizer_HitsPerEvent_int";
 	const std::string kThetaCenterParamKey = "EventCategorizer_ThetaCenter_float";
	const std::string kThetaLimesParamKey = "EventCategorizer_ThetaLimes_float";
	const std::string kTOTNoiseParamKey = "EventCategorizer_TOTNoise_float";
	const std::string kTOTPromptParamKey = "EventCategorizer_TOTPrompt_float";
	const std::string kIsUsedDataFromSimulationParamKey = "EventCategorizer_UsedDataFromSimulation_bool";
    FiltersManager* fFiltersManager;

      bool fIsUsedDataFromSimulation = false;
};
#endif /*  !EVENTCATEGORIZER_H */
