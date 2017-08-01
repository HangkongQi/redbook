cmake_minimum_required(VERSION 3.8)
project(redbook)
set(CMAKE_CXX_STANDARD 11)

set(TOOLS_SOURCE tools/LoadShaders.cpp tools/LoadShaders.h)

set(CH01_TRIANGLES ch01/triangles/triangles.cpp tools/vgl.h)
add_executable(triangles ${TOOLS_SOURCE} ${CH01_TRIANGLES})
target_link_libraries(triangles GL GLU glut m)