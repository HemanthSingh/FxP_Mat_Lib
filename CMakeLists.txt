cmake_minimum_required(VERSION 2.8.9)
project(Fixed_lib)

#Bring the headers, such as Student.h into the project

include_directories(include)
include_directories ("${PROJECT_SOURCE_DIR}/libarm/include") 
#include_directories ("${PROJECT_SOURCE_DIR}/libcordic/include") 

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -Wall")
add_subdirectory (libarm) 
add_subdirectory (libcordic) 
file(GLOB SOURCES "src/*.c")
add_executable(fixed_lib ${SOURCES})
target_link_libraries (fixed_lib m)
target_link_libraries (fixed_lib libcordic)
target_link_libraries (fixed_lib libarm)

#install(TARGETS testStudent DESTINATION /usr/lib)

