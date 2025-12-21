# d3d9 wrapper (Windows only)
# This is a Direct3D 9 wrapper for auto-update functionality

set(D3D9_SOURCES
    dllmain.cpp
    filedl.cpp
)

set(D3D9_HEADERS
    filedl.h
)

add_library(d3d9 SHARED
    ${D3D9_SOURCES}
    ${D3D9_HEADERS}
)

set_target_properties(d3d9 PROPERTIES
    OUTPUT_NAME "d3d9"
    SUFFIX ".dll"
)

target_link_libraries(d3d9 PRIVATE
    winhttp
)

if(MSVC)
    target_compile_options(d3d9 PRIVATE /W4)
endif()
