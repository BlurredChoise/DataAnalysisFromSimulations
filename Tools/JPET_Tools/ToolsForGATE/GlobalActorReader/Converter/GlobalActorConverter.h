#ifndef GlobalActorConverter_h
#define GlobalActorConverter_h
#include "Event.h"
#include "../GlobalActorReader.h"
#include <string>

class GlobalActorConverter
{
 public:
  GlobalActorConverter();
  ~GlobalActorConverter();
  static void transformToEventTree( const std::string &inFileName, const std::string &outFileName );
 private:
  static void addEntryToEvent( const ToolsForGATE::GlobalActorReader &gar, JPetGATEEvent *outEvent );
  static void clearEvent( JPetGATEEvent *outEvent );
};

#endif
