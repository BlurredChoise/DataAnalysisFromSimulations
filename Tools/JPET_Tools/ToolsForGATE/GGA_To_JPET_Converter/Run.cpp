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
#include "../GlobalActorReader/Converter/GlobalActorConverter.h"
#include <stdexcept>
#include <string>

/**
Code below is just example - modifie as you wish, but remember to take care of exceptions
*/
int main(int argc, char *argv[])
{
 const int required_arguments_number = 3;

 if( argc != required_arguments_number )
 {
  std::cerr << "Invalid number of variables. Call e.g. ./gga_to_jpet_conv input_file_name output_file_name" << std::endl;
 }
 else
 {
  std::string input_file_name( argv[1] );
  std::string output_file_name( argv[2] );

  std::cout << "PARAMATERS\nInput file: " << input_file_name << "\nOuput file: " << output_file_name << std::endl;

  std::cout << "Starting converting to event tree ... " << std::endl;
  GlobalActorConverter::transformToEventTree( input_file_name, output_file_name );
  std::cout << "Work done." << std::endl;
 }

 return 0;
}

