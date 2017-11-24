
set(TOOLS_SOURCES
        vgl.h
        LoadShaders.h
        LoadShaders.cpp
        )

add_library(gltools SHARED ${TOOLS_SOURCES})