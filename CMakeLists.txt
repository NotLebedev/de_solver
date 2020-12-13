cmake_minimum_required(VERSION 3.16)
project(de_solver C)

set(CMAKE_C_STANDARD 99)

add_executable(de_solver main.c RK.c RK.h functions.c boundary.c boundary.h)
target_link_libraries(de_solver m)