set(CH01_TRIANGLE_SOURCES triangles/triangles.cpp)

set(LOCAL_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(LOCAL_PATH_STR \"${LOCAL_PATH}/\")

include_directories(../tools)
link_libraries(gltools)

add_executable(triangles ${CH01_TRIANGLE_SOURCES})