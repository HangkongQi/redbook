cmake_minimum_required(VERSION 3.8)
project(redbook)
set(CMAKE_CXX_STANDARD 11)

set(TOP_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(TOP_PATH_STR \"${TOP_PATH}/\")
configure_file(
        ${TOP_PATH}/tools/curr_config.h.in
        ${TOP_PATH}/tools/curr_config.h
)

include_directories(/home/qihangkong/usr/include)
link_directories(/home/qihangkong/usr/lib)
link_libraries(GL GLU glut)

add_executable(triangle_test test.cpp radeonsi_test/test1.cpp)

add_executable(rtest1 radeonsi_test/test1.cpp radeonsi_test/testvulkan.cpp)

add_subdirectory(tools)
add_subdirectory(ch01)