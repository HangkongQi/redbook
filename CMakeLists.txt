cmake_minimum_required(VERSION 3.8)
project(redbook)
set(CMAKE_CXX_STANDARD 11)

set(TOP_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(TOP_PATH_STR \"${TOP_PATH}/\")
configure_file(
        ${TOP_PATH}/tools/curr_config.h.in
        ${TOP_PATH}/tools/curr_config.h
)

link_libraries(GL GLU glut)

add_subdirectory(tools)
include_directories(tools)
link_libraries(gltools)

add_subdirectory(ch01)
add_subdirectory(ch02)