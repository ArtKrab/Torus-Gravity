cmake_minimum_required(VERSION 3.15)
project(Course_work_task5 C) #change project name here

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(Course_work_task5 main.c sdl_aux.c sdl_aux.h vector.c vector.h model.c model.h) #change project name here

target_link_libraries(Course_work_task5 ${SDL2_LIBRARY}) #change project name here
