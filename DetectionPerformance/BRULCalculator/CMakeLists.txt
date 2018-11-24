cmake_minimum_required(VERSION 2.6)

##Author: Mateusz Bała
##E-mail: bala.mateusz@gmail.com
##File: CMakeLists.txt

#MANDATORY: Before first cmake please insert here your path to ROOT installation directory
#set(ROOT_INSTALLATION_DIRECTORY "/path/to/ROOT/installation/directory")
set(ROOT_INSTALLATION_DIRECTORY "/home/mateusz/Libraries/Installed/root")

################################################################################
# Handling of thisroot.sh
################################################################################

message(STATUS "Your ROOT installation directory is: ${ROOT_INSTALLATION_DIRECTORY}")

if(EXISTS ${ROOT_INSTALLATION_DIRECTORY}/bin/thisroot.sh)
  message(STATUS "Status of thisroot.sh file : EXIST")
else()
 message(FATAL_ERROR "Status of thisroot.sh file :  DOES NOT EXIST - is your path to ROOT installation directory is correct? Please check a variable ROOT_INSTALLATION_DIRECTORY in this CMakeList.txt file.")
endif()

message(STATUS "Calling thisroot.sh")
execute_process(COMMAND source ${ROOT_INSTALLATION_DIRECTORY}/bin/thisroot.sh)

################################################################################
# Project configuration
################################################################################

set(projectName BranchingRatioUpperLimitCalculator)
set(projectBinary ${projectName}.x)

project(${projectName} CXX) # using only C++

add_definitions(-std=c++11) # using C++11 standard

################################################################################
# Handling of ROOT 
################################################################################

# first, try the old-school ROOTSYS variable
set(root_prefix $ENV{ROOTSYS})
if(root_prefix)
  list(APPEND CMAKE_MODULE_PATH ${root_prefix}/etc/cmake/)  
endif()

# try also a search based on root-config
execute_process(COMMAND root-config --etcdir OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
list(APPEND CMAKE_MODULE_PATH ${ROOT_ETCDIR}/cmake)

find_package(ROOT QUIET)

if(ROOT_FOUND)
  message(STATUS "Found ROOT version: ${ROOT_VERSION} (${ROOT_CONFIG_EXECUTABLE})")
else()
  # if we failed with CMake based find_package, use fallback
  # root-config version from cmake/fallback/
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/fallback)
  message(WARNING "No CMake modules from a ROOT installation found. Trying fallback mode.")
  find_package(ROOT 5 REQUIRED)
endif()

if(ROOT_USE_FILE)
  include(${ROOT_USE_FILE})
endif()

################################################################################
# Sources and linking 
################################################################################

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

#code from Tools for ROOT
set(tools_root_dir "../../Tools/ToolsForROOT")
file(GLOB HEADERS1 ${tools_root_dir}/*.h)
file(GLOB SOURCES1 ${tools_root_dir}/*.cpp)

add_executable(brul_calc ${SOURCES} ${SOURCES1})

target_link_libraries(brul_calc ${ROOT_LIBRARIES})
