add_executable(MainCD1D main_cond.cpp fifo.py)
target_link_libraries(MainCD1D thermal)

add_executable(MainCDCV1D main_conv.cpp fifo.py)
target_link_libraries(MainCDCV1D thermal)

add_executable(MainCD2D main_cond_2d.cpp fifo2D.py)
target_link_libraries(MainCD2D thermal)