
set(TOOLS_SOURCES
        vgl.h
        LoadShaders.h
        LoadShaders.cpp
        vmath.h vmath.cpp)

add_library(gltools SHARED ${TOOLS_SOURCES})