#ifndef Message_h
#define Message_h
#include <string>
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This is simple static class which checks given value and display proper communicat if this this value is false.
*/

namespace ToolsForROOT
{
 class Message
 {
  public:
   static bool check( const bool value_to_check, std::string message_to_display );
   static bool error( const bool value_to_check, std::string message_to_display );
   static bool warning( const bool value_to_check, std::string message_to_display );
 };
};

#endif
