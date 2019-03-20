cmake_minimum_required(VERSION 3.13)
project(lab_mpi)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab_mpi main.cpp)


SET_TARGET_PROPERTIES(lab_mpi PROPERTIES COMPILE_FLAGS "-fopenmp"
        LINK_FLAGS "-fopenmp")
#
#PROJECT(lab_mpi)
#ADD_EXECUTABLE(test main.cpp)
#SET(CMAKE_C_COMPILER mpicc)
#SET(CMAKE_CXX_COMPILER mpicxx)
#target_link_libraries(test mpi)

