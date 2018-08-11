/**
 *  @copyright Copyright 2018 The J-PET Gate Authors. All rights reserved.
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  @file GlobalActorReader.cpp
 */

#include<iostream>
#include "GlobalActorReader.h"
#include "TMath.h"

namespace ToolsForGATE
{

GlobalActorReader::GlobalActorReader()
{
 fEntriesNumber = 0;
 fInitializedVariablesNumber = 0;
 fCurrentEntryIndex = 0;
 fGenerator.initGenerator();
}

GlobalActorReader::~GlobalActorReader() { reset(); }

bool GlobalActorReader::loadFile( const std::string& file_name )
{
 std::string fname = file_name;
 if ( !fname.size() )
  return false;
 if ( fname.rfind(".root") == std::string::npos )
  fname += ".root";
 pFile = new TFile( fname.c_str(), "READ" );
 if ( !pFile->IsOpen() )
  return false;
 pTree = dynamic_cast<TTree*>( pFile->Get("GateGlobalActorTree") );
 if ( !pTree )
  return false;
 initVariables();
 fEntriesNumber = pTree->GetEntries();
 return fInitializedVariablesNumber > 0;
}

bool GlobalActorReader::read()
{
 if ( fCurrentEntryIndex < fEntriesNumber && pTree )
  pTree->GetEntry( fCurrentEntryIndex );
 else
  return false;
 ++fCurrentEntryIndex;
 return true;
}

void GlobalActorReader::execute( std::string input_file_name, ToolsForAnalysis::AnalysisClass* ac, ToolsForAnalysis::AnalysisDataCreatorClass* dcc )
{
 if ( !loadFile( input_file_name ) )
  return;
 while( read() )
 {
  dcc->extractDataFromEntry();
  ac->analyzeEntry();
 }
}

int GlobalActorReader::getEntriesNumber() const { return fEntriesNumber; }

int GlobalActorReader::getInitializedVariablesNumber() const { return fInitializedVariablesNumber; }

void GlobalActorReader::reset()
{
 fEntriesNumber = 0;
 fInitializedVariablesNumber = 0;
 fCurrentEntryIndex = 0;
}

void GlobalActorReader::initVariables()
{
 if( !pTree )
 {
  std::cerr<<"pTree null poiter in InitVariables"<<std::endl;
  return;
 }
 notice( fVolumeName.tryAttachToBranch( &pTree, "VolumeName" ) );
 notice( fScintilatorPosition.tryAttachToBranch( &pTree, "ScintilatorPosition") );
 notice( fEventID.tryAttachToBranch( &pTree, "EventID") );
 notice( fTrackID.tryAttachToBranch( &pTree, "TrackID") );
 notice( fEnergyBeforeProcess.tryAttachToBranch( &pTree, "EnergyBeforeProcess") );
 notice( fEnergyAfterProcess.tryAttachToBranch( &pTree, "EnergyAfterProcess") );
 notice( fEnergyLossDuringProcess.tryAttachToBranch( &pTree, "EnergyLossDuringProcess") );
 notice( fMomentumDirectionBeforeProcess.tryAttachToBranch( &pTree, "MomentumDirectionBeforeProcess") );
 notice( fMomentumDirectionAfterProcess.tryAttachToBranch( &pTree, "MomentumDirectionAfterProcess") );
 notice( fProcessPosition.tryAttachToBranch( &pTree, "ProcessPosition") );
 notice( fEmissionPointFromSource.tryAttachToBranch( &pTree, "EmissionPointFromSource") );
 notice( fEmissionMomentumDirectionFromSource.tryAttachToBranch( &pTree, "EmissionMomentumDirectionFromSource") );
 notice( fEmissionEnergyFromSource.tryAttachToBranch( &pTree, "EmissionEnergyFromSource") );
 notice( fParticleName.tryAttachToBranch( &pTree, "ParticleName") );
 notice( fParticlePGDCoding.tryAttachToBranch( &pTree, "ParticlePGDCoding") );
 notice( fProcessAngle.tryAttachToBranch( &pTree, "ProcessAngle") );
 notice( fPolarizationBeforeProcess.tryAttachToBranch( &pTree, "PolarizationBeforeProcess") );
 notice( fPolarizationAfterProcess.tryAttachToBranch( &pTree, "PolarizationAfterProcess") );
 notice( fProcessName.tryAttachToBranch( &pTree, "ProcessName") );
 notice( fParentID.tryAttachToBranch( &pTree, "ParentID") );
 notice( fInteractionTime.tryAttachToBranch( &pTree, "InteractionTime") );
 notice( fLocalTime.tryAttachToBranch( &pTree, "LocalTime") );
 notice( fGlobalTime.tryAttachToBranch( &pTree, "GlobalTime") );
 notice( fProperTime.tryAttachToBranch( &pTree, "ProperTime") );
}

void GlobalActorReader::notice(const bool& value)
{
 if( value )
  ++fInitializedVariablesNumber;
}

std::string GlobalActorReader::getVolumeName() const { return fVolumeName.getValue(); }

TVector3 GlobalActorReader::getScintilatorPosition() const { return fScintilatorPosition.getValue(); }

int GlobalActorReader::getEventID() const { return fEventID.getValue(); }

int GlobalActorReader::getTrackID() const { return fTrackID.getValue(); }

double GlobalActorReader::getEnergyBeforeProcess() const { return fEnergyBeforeProcess.getValue(); }

double GlobalActorReader::getEnergyAfterProcess() const { return fEnergyAfterProcess.getValue(); }

double GlobalActorReader::getEnergyLossDuringProcess() const { return fEnergyLossDuringProcess.getValue(); }

TVector3 GlobalActorReader::getMomentumDirectionBeforeProcess() const { return fMomentumDirectionBeforeProcess.getValue(); }

TVector3 GlobalActorReader::getMomentumDirectionAfterProcess() const { return fMomentumDirectionAfterProcess.getValue(); }

TVector3 GlobalActorReader::getProcessPosition() const { return fProcessPosition.getValue(); }

TVector3 GlobalActorReader::getEmissionPointFromSource() const { return fEmissionPointFromSource.getValue(); }

TVector3 GlobalActorReader::getEmissionMomentumDirectionFromSource() const { return fEmissionMomentumDirectionFromSource.getValue(); }

double GlobalActorReader::getEmissionEnergyFromSource() const { return fEmissionEnergyFromSource.getValue(); }

std::string GlobalActorReader::getParticleName() const { return fParticleName.getValue(); }

int GlobalActorReader::getParticlePGDCoding() const { return fParticlePGDCoding.getValue(); }

double GlobalActorReader::getProcessAngle() const { return fProcessAngle.getValue(); }

TVector3 GlobalActorReader::getPolarizationBeforeProcess() const { return fPolarizationBeforeProcess.getValue(); }

TVector3 GlobalActorReader::getPolarizationAfterProcess() const { return fPolarizationAfterProcess.getValue(); }

std::string GlobalActorReader::getProcessName() const { return fProcessName.getValue(); }

int GlobalActorReader::getParentID() const { return fParentID.getValue(); }

double GlobalActorReader::getInteractionTime() const { return fInteractionTime.getValue(); }

double GlobalActorReader::getLocalTime() const { return fLocalTime.getValue(); }

double GlobalActorReader::getGlobalTime() const { return fGlobalTime.getValue(); }

double GlobalActorReader::getProperTime() const { return fProperTime.getValue(); }

double GlobalActorReader::getComptonThetaValue()
{
 TVector3 k0 = fMomentumDirectionBeforeProcess.getValue();
 TVector3 k = fMomentumDirectionAfterProcess.getValue();
 return k0.Angle( k ) * TMath::RadToDeg();
}

double GlobalActorReader::getComptonPhiValue()
{
 //This is based on article "New Monte Carlo method for Compton and Rayleigh scattering by polarized gamma rays ,G.O. Depaola"
 double phi = 0;
 TVector3 e0 = fPolarizationBeforeProcess.getValue();
 if ( e0.Mag() == 0 )
 {
  phi = M_PI* ( 2.0 * fGenerator.getValueFromUniformDistribution() - 1.0 );
 }
 else
 {
  TVector3 k0 = fMomentumDirectionBeforeProcess.getValue();
  TVector3 k = fMomentumDirectionAfterProcess.getValue();

  double sinTheta = sin( k0.Angle( k ) );
  phi = sinTheta == 0 ? M_PI * ( 2.0 * fGenerator.getValueFromUniformDistribution() - 1.0 ) : TMath::ACos( k.Dot( e0 ) / sinTheta );

  if( k.Dot( k0.Cross( e0 ).Unit() ) < 0)
   phi *= -1.0;
 }
 return phi * TMath::RadToDeg();
}

};
