cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Tools/j-pet-framework/cmake)

# add Framework submodule
add_subdirectory(Tools/j-pet-framework)
include_directories(Tools/j-pet-framework ${Framework_INCLUDE_DIRS})
add_definitions(${Framework_DEFINITIONS})

add_definitions(-std=c++11 -Wall -Wunused-parameter)

add_subdirectory(Tools/ToolsForG4MC)
