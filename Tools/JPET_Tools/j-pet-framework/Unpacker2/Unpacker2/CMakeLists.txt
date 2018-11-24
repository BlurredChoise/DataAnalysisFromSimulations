cmake_minimum_required(VERSION 2.6)

project(Unpacker2 CXX)

if(NOT MSVC)
  add_definitions(-std=c++11 -Wall -Wunused-parameter)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# add possible ROOT cmake module locations to module path
execute_process(COMMAND root-config --etcdir OUTPUT_VARIABLE ROOT_ETCDIR OUTPUT_STRIP_TRAILING_WHITESPACE)
list(APPEND CMAKE_MODULE_PATH ${ROOT_ETCDIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS}/etc/cmake)

# find ROOT
find_package(ROOT 5 REQUIRED)

if(ROOT_USE_FILE)
  include(${ROOT_USE_FILE})
endif()

include_directories(${ROOT_INCLUDE_DIRS})
add_definitions(${ROOT_DEFINITIONS})

find_package(Boost 1.50.0 REQUIRED
             unit_test_framework
            )
include_directories(${Boost_INCLUDE_DIRS})
add_definitions(${Boost_DEFINITIONS})

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cc)

set(DICTIONARY_REQUIRED
  Event.h
  Hit.h
  EventIII.h
  TDCChannel.h
  TDCHit.h
  TDCHitExtended.h
  TDCHitIII.h
  )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
foreach(header ${DICTIONARY_REQUIRED})
  ROOT_GENERATE_DICTIONARY(${header}_Dict ${header} OPTIONS -p)
  list(APPEND SOURCES ${header}_Dict.cxx)
endforeach()

add_library(Unpacker2 SHARED ${SOURCES} ${HEADERS})

target_link_libraries(Unpacker2
  ${Boost_LIBRARIES}
  ${ROOT_LIBRARIES}
  )

set_target_properties(Unpacker2 PROPERTIES LINKER_LANGUAGE CXX)

#unit tests
set(TESTS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

foreach(dir ${TESTS_SOURCE_DIR})
  file(GLOB UNIT_TEST_SOURCES_TMP ${dir}/*Test.cpp)
  list(APPEND UNIT_TEST_SOURCES ${UNIT_TEST_SOURCES_TMP})
endforeach()

set(TESTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/tests)
file(MAKE_DIRECTORY ${TESTS_DIR})
file(COPY unitTestUtils/run_tests.pl DESTINATION ${TESTS_DIR})
file(COPY unitTestUtils/parseXML.py DESTINATION ${TESTS_DIR})
foreach(test_source ${UNIT_TEST_SOURCES})
  get_filename_component(test ${test_source} NAME_WE)
  list(APPEND test_binaries ${test}.x)
  add_executable(${test}.x EXCLUDE_FROM_ALL ${test_source})
  set_target_properties(${test}.x PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_DIR} )
  target_link_libraries(${test}.x
          Unpacker2
          ${Boost_LIBRARIES}
          )
endforeach()

add_custom_target(unpacker_tests DEPENDS ${test_binaries} Unpacker2) 
