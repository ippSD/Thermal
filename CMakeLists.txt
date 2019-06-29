cmake_minimum_required(VERSION 3.14)
project(Main_C_2D)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Thermal)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
add_subdirectory (docs)
add_executable(Main_C main_cond.cpp Thermal/thermal.cpp)
add_executable(Main_CC main_conv.cpp Thermal/thermal.cpp)
add_executable(Main_C_2D main_cond_2d.cpp Thermal/thermal.cpp)
target_include_directories(Main_CC PUBLIC .)
#
