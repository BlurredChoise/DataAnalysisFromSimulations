#include <iostream>
#include "Message.h"
/**
Author: Mateusz Bała
E-mail: bala.mateusz@gmail.com
About: This is simple static class which checks given value and display proper communicat if this this value is false.
*/

namespace ToolsForROOT
{
 bool Message::check( const bool value_to_check, std::string message_to_display )
 {
  if( !value_to_check )
   std::cout << message_to_display << std::endl;
  return value_to_check;
 }

 bool Message::error( const bool value_to_check, std::string message_to_display )
 {
  return !check( value_to_check, "[ERROR] " + message_to_display );
 }

 bool Message::warning( const bool value_to_check, std::string message_to_display )
 {
  return !check( value_to_check, "[WARNING] " + message_to_display );
 }
};
