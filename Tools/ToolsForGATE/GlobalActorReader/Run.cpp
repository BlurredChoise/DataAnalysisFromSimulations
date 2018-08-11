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
 *  @file Run.cc
 */
#include <iostream>
#include "GlobalActorReader.h"
#include <stdexcept>
using namespace std;

/**
Code below is just example - modifie as you wish, but remember to take care of exceptions
*/
int main(int argc, char *argv[])
{
 if(argc != 2)
 {
  std::cerr<<"Invalid number of variables. Call e.g. ./gar file_name.root or ./gar file_name"<<std::endl;
 }
 else
 {
  std::string file_name(argv[1]);
  try
  {
   ToolsForGATE::GlobalActorReader gar;
   if( gar.loadFile(file_name) )
    while( gar.read() )
    {
     //Your code
    }
    else
     std::cerr<<"Loading file failed."<<std::endl;
     return 1;
    }
    catch(const std::logic_error& e )
    {
     std::cerr<<e.what()<<std::endl;
     return 1;
    }
    catch(...)
    {
     std::cerr<<"Udefined exception"<<std::endl;
     return 1;
    }
   }
    return 0;
}

