# J-PET tool project using J-PET framework
#
# Author: Adam Strzelecki <adam.strzelecki@uj.edu.pl>
#
# Description:
#   Builds project depending on J-PET framework.

cmake_minimum_required(VERSION 2.6)

######################################################################
### when creating a new project,
### set this section appropriately for your project
######################################################################
set(projectName txt_conv_g4mc)

set(ROOT_SCRIPTS
  rootlogon.C
  rootalias.C
  )

######################################################################
### this section should not need to be modified for a new project
######################################################################
set(projectBinary ${projectName}.x)

project(${projectName} CXX) # using only C++

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)
#file(GLOB MAIN_CPP main.cpp)
##################
set(tools_geant4_dir "../../Tools/ToolsForG4MC")
file(GLOB HEADERS1 ${tools_geant4_dir}/G4MCReader/G4MCReader.h)
file(GLOB SOURCES1 ${tools_geant4_dir}/G4MCReader/G4MCReader.cpp)

file(GLOB HEADERS2 ${tools_geant4_dir}/G4MCHitData/G4MCHitData.h)
file(GLOB SOURCES2 ${tools_geant4_dir}/G4MCHitData/G4MCHitData.cpp)

set( tools_analysis_dir "../../Tools/ToolsForAnalysis" )
file(GLOB HEADERS3 ${tools_analysis_dir}/*.h)
file(GLOB SOURCES3 ${tools_analysis_dir}/*.cpp)

set( tools_root_dir "../../Tools/ToolsForROOT" )
file(GLOB HEADERS4 ${tools_root_dir}/*.h)
file(GLOB SOURCES4 ${tools_root_dir}/*.cpp)

set( models_dir "TXTModels" )
file(GLOB HEADERS5 ${models_dir}/*.h)
file(GLOB SOURCES5 ${models_dir}/*.cpp)

####################
include_directories(${Framework_INCLUDE_DIRS})
add_definitions(${Framework_DEFINITIONS})

add_executable(${projectBinary} ${SOURCES} ${HEADERS} ${SOURCES1} ${HEADERS1} ${SOURCES2} ${HEADERS2} ${SOURCES3} ${HEADERS3} ${SOURCES4} ${HEADERS4} ${SOURCES5} ${HEADERS5})
target_link_libraries(${projectBinary} JPetFramework)

set(copy_depends) #create variable for list with depends files path

# copy the example auxilliary files
foreach( file_i ${AUXILLIARY_FILES})
  list(APPEND copy_depends ${CMAKE_CURRENT_BINARY_DIR}/${file_i})

  if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${file_i})
    set(CP_CMD copy_directory)
  else()
    set(CP_CMD copy)
  endif()
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${file_i}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E ${CP_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/../${file_i} ${CMAKE_CURRENT_BINARY_DIR}/${file_i}
    )
endforeach( file_i )

# copy the ROOT scripts
foreach( file_i ${ROOT_SCRIPTS})
  list(APPEND copy_depends ${CMAKE_CURRENT_BINARY_DIR}/${file_i})
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${file_i}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E ${CP_CMD} ${CMAKE_CURRENT_SOURCE_DIR}/../scripts/${file_i} ${CMAKE_CURRENT_BINARY_DIR}/${file_i}
    )
endforeach( file_i )

add_custom_target(copy_files_${projectName} DEPENDS ${copy_depends}) #add new target that depends on copied files
add_dependencies(${projectBinary} copy_files) #add dependencies between building project and copy files
