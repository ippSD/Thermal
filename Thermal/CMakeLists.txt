add_library (thermal_1d OBJECT thermal_1d.cpp thermal_1d.h thermal_data.h)
target_include_directories(thermal_1d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library (thermal_2d OBJECT thermal_2d.cpp thermal_2d.h thermal_data.h)
target_include_directories(thermal_2d PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})