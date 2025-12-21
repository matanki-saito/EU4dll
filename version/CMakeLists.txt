# version checker (Windows only)

set(VERSION_SOURCES
    dllmain.cpp
    auto_update.cpp
)

set(VERSION_HEADERS
    auto_update.h
)

add_library(version SHARED
    ${VERSION_SOURCES}
    ${VERSION_HEADERS}
)

set_target_properties(version PROPERTIES
    OUTPUT_NAME "version"
    SUFFIX ".dll"
)

if(MSVC)
    target_compile_options(version PRIVATE /W4)
endif()
