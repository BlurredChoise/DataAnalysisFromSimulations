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
 *  @file GlobalActorReader.h
 */
#ifndef GLOBALACTORREADER_H
#define GLOBALACTORREADER_H
#include "Variable.h"
#include "TTree.h"
#include "TFile.h"
#include "TVector3.h"
#include "../../ToolsForROOT/RandomGenerator.h"
#include "../../ToolsForAnalysis/AnalysisClass.h"
#include "../../ToolsForAnalysis/AnalysisDataCreatorClass.h"

namespace ToolsForGATE
{

 /** @About: This class is a reader of data from GateGlobalActor.
  * Thanks to simple implementation you just need to declar variable and add initialization of variable in InitVariable() to obtain access to data from file.
  * @Author: Mateusz Bała
  * @Email: bala.mateusz@gmail.com
 **/
 class GlobalActorReader
 {
  public:
   GlobalActorReader();
   ~GlobalActorReader();

   /** Function try open file and get acces to tree.
    * @param: file_name - ROOT file name
    * @return: false - when file does not exist, tree does not exist or tree is empty, otherwise true
   */
   bool loadFile(const std::string& file_name);

   /** Function read data from tree. Each call of this function call next entity.
    * @return : false - when function reach maximal number of entries in tree, true - otherwise
   */
   bool read();

   /** Resturn number number of entries in tree.
   */
   int getEntriesNumber() const;

   /** Return number of initialized variables
    */
   int getInitializedVariablesNumber() const;

   /** Reset counters and close file.
    */
   void reset();

   void execute( std::string input_file_name, ToolsForAnalysis::AnalysisClass* ac, ToolsForAnalysis::AnalysisDataCreatorClass* dcc );

   void stopJob();

  private:
   /** Try init variables. Use this function to read your variable.
    * You just need to add in this function : Notice(yourVariable.TryAttachToBranch(mTree, "yourBranchName");
   */
   void initVariables();

   /** This function counter number of initialized variables.
    * @param: value - value from clas Variable function TryAttachToBranch
   */
   void notice(const bool& value);

   //ROOT file
   TFile* pFile;
   //Tree from mFile
   TTree* pTree;
   //Number of initialized variables
   int fInitializedVariablesNumber;
   //Number of entries in tree
   int fEntriesNumber;
   //Current index of entry
   int fCurrentEntryIndex;

   bool fStopJob = false;

  public:
  /** GET-functions.
    * This is only way how you return values;
    * For more informations check variables descriptions.
   **/

   std::string getVolumeName() const;

   TVector3 getScintilatorPosition() const;

   int getEventID() const;

   int getTrackID() const;

   double getEnergyBeforeProcess() const;

   double getEnergyAfterProcess() const;

   double getEnergyLossDuringProcess() const;

   TVector3 getMomentumDirectionBeforeProcess() const;

   TVector3 getMomentumDirectionAfterProcess() const;

   TVector3 getProcessPosition() const;

   TVector3 getEmissionPointFromSource() const;

   TVector3 getEmissionMomentumDirectionFromSource() const;

   double getEmissionEnergyFromSource() const;

   std::string getParticleName() const;

   int getParticlePGDCoding() const;

   double getProcessAngle() const;

   TVector3 getPolarizationBeforeProcess() const;

   TVector3 getPolarizationAfterProcess() const;

   std::string getProcessName() const;

   int getParentID() const;

   double getInteractionTime() const;

   double getLocalTime() const;

   double getGlobalTime() const;

   double getProperTime() const;

  private:
  /** VARIABLES
    * Declar here your variable by using template class Variable<yourType>
    * Please add description of your variable here
   **/

   //Volume name (layer name) - this variable tell in which volume (layer) something happened e.g. gamma scattered in volume wit name "LayerA"
   Variable<std::string, true> fVolumeName;
   //Scintilator translation vector (if detector does not rotate it is equal scintilator centrum position) - this is useful when you want to know where exacly process happened (from VolumeName you know layer and from ScintilatorPosition you know which scintilator)
   Variable<TVector3, true> fScintilatorPosition;
   //Event ID - this variable tell you which event is related to particle e.g. you have e+ and gamma - both created during event no 1 (both has the same EventID)
   Variable<int, false> fEventID;
   //Track ID - each EventID has one or more tracks e.g. e+ and 2 gammas from e+ annihilation - both has EventID=1, e+ has trackID=1, gamma no 1 has trackID=2, gamma no 2 has trackID = 3
   Variable<int, false> fTrackID;
   //Particle energy before process (e.g. before scattering) - the unit of energy is keV
   Variable<double, false> fEnergyBeforeProcess;
   //Particle energy after process (e.g. after scattering) - the unit of energy is keV
   Variable<double, false> fEnergyAfterProcess;
   //Particle energy loss during process (e.g. during scattering) - this is exactly this: EnergyLossDuringProcess = EnergyBeforeProcess - EnergyAfterProcess; the unit of energy is keV
   Variable<double, false> fEnergyLossDuringProcess;
   //Particle momemntum direction before process (e.g. before scattering)
   Variable<TVector3, true> fMomentumDirectionBeforeProcess;
   //Particle momemntum direction after process (e.g. after scattering)
   Variable<TVector3, true> fMomentumDirectionAfterProcess;
   //Process position in lab coordinate system - by this variable you know where exacly process happened
   Variable<TVector3, true> fProcessPosition;
   //Emission point from source - by this variable you know position of source which emitted particle
   Variable<TVector3, true> fEmissionPointFromSource;
   //Particle momentum direction just after emission from source
   Variable<TVector3, true> fEmissionMomentumDirectionFromSource;
   //Particle energy just after emission from source - the unit of energy is keV
   Variable<double, false> fEmissionEnergyFromSource;
   //Particle name e.g. gamma, e+, e-, etc. You can find particle name by checking Geant4 particle class and looking at parameter "aName" in G4ParticleDefinition constructor (it's 1st argument of constructor).  For some examples check this: https://agenda.infn.it/getFile.py/access?sessionId=26&resId=0&materialId=0&confId=12061
   Variable<std::string, true> fParticleName;
   //Particle PDG code - e.g. gamma has 0. You can find pdg code of particle by checking Geant4 particle class and looking at parameter "encoding" in G4ParticleDefinition constructor (it's 14th argument of constructor). For some examples check this: https://agenda.infn.it/getFile.py/access?sessionId=26&resId=0&materialId=0&confId=12061
   Variable<int, false> fParticlePGDCoding;
   //Angle betwean particle momentum before and after process
   Variable<double, false> fProcessAngle;
   //Particle polarization before process happened
   Variable<TVector3, true> fPolarizationBeforeProcess;
   //Particle polarization after process happened
   Variable<TVector3, true> fPolarizationAfterProcess;
   //Process name e.g. "Compton", "Ionization", etc. - if you use Gate physics lists, "compt", etc. - if you use Geant4 physics lists. For GATE check this page: http://wiki.opengatecollaboration.org/index.php/Users_Guide:Setting_up_the_physics ; for Geant4 find specific class and/or check Geant4 documentation
   Variable<std::string, true> fProcessName;
   //Parent ID - parent ID tell which track created current track e.g e+ has EventID = 1 and TrackID=1 and e+ decay to 2 gammas, gamma has EventID=1, TrackID=2, ParentID=1 etc.
   Variable<int, false> fParentID;
   //Interaction time - difference between local time of pre and post step of track
   Variable<double, false> fInteractionTime;
   //Local time - time since the track was created
   Variable<double, false> fLocalTime;
   //Global time -  time since the event was created
   Variable<double, false> fGlobalTime;
   //Proper time -  time in its rest frame since the track was created
   Variable<double, false> fProperTime;
  private:
   ToolsForROOT::RandomGenerator fGenerator;

  public:
  /** EXTRA FUNCTIONS
    * If you need variable which is based on other variables lisetd in InitVariables().
    * Please add here your GetSthValue() e.g. GetComptonThetaValue();
    * Remember add decription of file
   **/

   /** Return Compton scaterring angle (theta angle).
    * This is angle betwean prime and scattered gamma momentum direction.
    * Angle unit: degree
   **/
   double getComptonThetaValue();

   /** Return Compton phi angle.
    * This is angle betwean prime gamma polarization vector and scattered gamma momentum vector throw on
    * the plane perpendicular to prime gamma momentum direction.
    * Angle unit: degree
   **/
  double getComptonPhiValue();
 };
};

#endif // GLOBALACTORREADER_HH
