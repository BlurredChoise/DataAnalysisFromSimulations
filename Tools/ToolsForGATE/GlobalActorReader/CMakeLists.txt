cmake_minimum_required(VERSION 2.6)

#MANDATORY: Before first cmake please insert here your path to ROOT installation directory
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

set(projectName GAR)
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

add_definitions(${ROOT_DEFINITIONS})

################################################################################
# Handling of BOOST
################################################################################

set(BOOST_LOG_DYN_LINK -DBOOST_LOG_DYN_LINK)
add_definitions(${BOOST_LOG_DYN_LINK})
find_package(Boost 1.50.0 REQUIRED COMPONENTS unit_test_framework )

message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

add_definitions(${Boost_DEFINITIONS})

################################################################################
# Sources and linking 
################################################################################

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

#code from Tools for ROOT
file(GLOB HEADERS2 ../../ToolsForROOT/*.h)
file(GLOB SOURCES2 ../../ToolsForROOT/*.cpp)
#code from Tools for analysis
file(GLOB HEADERS3 ../../ToolsForAnalysis/*.h)
file(GLOB SOURCES3 ../../ToolsForAnalysis/*.cpp)

################################################################################
# Unit tests
################################################################################
set(TESTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/tests)
file(MAKE_DIRECTORY ${TESTS_DIR})


add_executable(GAR ${SOURCES} ${SOURCES2} ${SOURCES3})

target_link_libraries(GAR ${ROOT_LIBRARIES})
