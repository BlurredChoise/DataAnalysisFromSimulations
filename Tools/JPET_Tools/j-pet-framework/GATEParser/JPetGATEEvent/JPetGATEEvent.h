/**
 *  @copyright Copyright 2018 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file Event.h
 */

#ifndef JPetGATEEvent_h 
#define JPetGATEEvent_h
#include <TObject.h>
#include <string>
#include <vector>
#include <JPetGATETrack/JPetGATETrack.h>
class JPetGATEEvent: public TObject {
public:
  JPetGATEEvent();
  int fEventID = -1;
  std::vector<JPetGATETrack> fTracks;
  ClassDef(JPetGATEEvent,1)
};
#endif /*  !EVENT_H */
