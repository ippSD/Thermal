cmake_minimum_required(VERSION 3.14)
project(Thermal)

set(CMAKE_CXX_STANDARD 14)

include_directories(Thermal)


add_subdirectory(Thermal)
add_library(thermal SHARED $<TARGET_OBJECTS:thermal_1d> $<TARGET_OBJECTS:thermal_2d>)

add_subdirectory(Examples)

#target_include_directories(MAIN_C PUBLIC .)
#add_executable(Main_C main_cond.cpp Thermal/thermal.cpp)
#target_link_libraries(lib)

#add_executable(Main_CC main_conv.cpp Thermal/thermal.cpp)
#add_executable(Main_C_2D main_cond_2d.cpp Thermal/thermal.cpp)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
add_subdirectory (docs)

#
