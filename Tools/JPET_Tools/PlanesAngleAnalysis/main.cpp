/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
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
 *  @file main.cpp
 */

#include <JPetManager/JPetManager.h>
//#include "../LargeBarrelAnalysis/UniversalFileLoader.h"
#include "../LargeBarrelAnalysis/TimeWindowCreator.h"
//#include "../LargeBarrelAnalysis/TimeCalibLoader.h"
#include "../LargeBarrelAnalysis/SignalFinder.h"
#include "../LargeBarrelAnalysis/SignalTransformer.h"
#include "../LargeBarrelAnalysis/HitFinder.h"
#include "../LargeBarrelAnalysis/EventFinder.h"
#include "EventCategorizer.h"
//#include "../LargeBarrelAnalysis/ImageReco.h"
#include<chrono>
#include <fstream>
#include <string>
using namespace std;

string GetTaskToDo()
{
 fstream f("/home/mbala/Run5Analysis/Programs/todo.status", ios::in);
 string todo;
 getline(f, todo);
 f.close();
 cout<<"PAA todo = >>"<<todo<<"<<"<<endl;
 return todo;
}

int main(int argc, const char* argv[])
{
  try {
    JPetManager& manager = JPetManager::getManager();
    
    manager.registerTask<EventFinder>("EventFinder");
    manager.registerTask<EventCategorizer>("EventCategorizer");
    
    manager.useTask("EventFinder", "mc.hits", "unk.evt");
    manager.useTask("EventCategorizer", "unk.evt", "cat.evt");
    
    manager.run(argc, argv);
  } catch (const std::exception& except) {
    std::cerr << "Unrecoverable error occured:" << except.what() << "Exiting the program!" << std::endl;
    return EXIT_FAILURE;
  }

//////////////////////////

 //string todo = GetTaskToDo();

 //JPetManager& manager = JPetManager::getManager();

 /*if ( todo == "TimeWindowCreator" )
 {
  manager.registerTask<TimeWindowCreator>("TimeWindowCreator");
  manager.useTask("TimeWindowCreator", "hld", "tslot.calib");
 }
 else if ( todo == "SignalFinder" )
 {
  manager.registerTask<SignalFinder>("SignalFinder");
  manager.useTask("SignalFinder", "tslot.calib", "raw.sig");
 }
 else if ( todo == "SignalTransformer" ) 
 {
  manager.registerTask<SignalTransformer>("SignalTransformer"); 
  manager.useTask("SignalTransformer", "raw.sig", "phys.sig");
 }
 else if ( todo == "HitFinder" )
 {
  manager.registerTask<HitFinder>("HitFinder"); 
  manager.useTask("HitFinder", "phys.sig", "hits");
 }
 else if ( todo == "EventFinder" )
 {
  manager.registerTask<EventFinder>("EventFinder");
  manager.useTask("EventFinder", "hits", "unk.evt");
 }
 else if ( todo == "EventCategorizer" )
 {*/
 //manager.registerTask<EventCategorizer>("EventCategorizer");
 // manager.useTask("EventCategorizer", "unk.evt", "cat.evt");
 /*}
 else
 {
  cout<<"Unknow command"<<endl;
  return 1;
 }*/

 // manager.run(argc, argv);
}
