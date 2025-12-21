set(PLUGIN64_SOURCES
    byte_pattern.cpp
    debug.cpp
    date.cpp
    escape_tool.cpp
    dll_main.cpp
    file_save.cpp
    event_dialog.cpp
    font.cpp
    ime.cpp
    input.cpp
    localization.cpp
    list_field_adjustment.cpp
    main_text.cpp
    map_justify.cpp
    map_adjustment.cpp
    map_popup.cpp
    map_nudge_view.cpp
    mod_download.cpp
    options.cpp
    map_view.cpp
    pch.cpp
    program.cpp
    tooltip_and_button.cpp
    version.cpp
    validator.cpp
)

set(PLUGIN64_HEADERS
    byte_pattern.h
    calling.hpp
    assembly.hpp
    escape_tool.h
    framework.h
    hooking.hpp
    injector.hpp
    mod_download.h
    plugin64.h
    plugin_64.h
    pch.h
    translator.hpp
    utility.hpp
)

# Create the shared library
add_library(Plugin64 SHARED
    ${PLUGIN64_SOURCES}
    ${PLUGIN64_HEADERS}
)

# Set output name based on platform
if(WIN32)
    set_target_properties(Plugin64 PROPERTIES
        OUTPUT_NAME "Plugin64"
        SUFFIX ".dll"
    )
elseif(APPLE)
    set_target_properties(Plugin64 PROPERTIES
        OUTPUT_NAME "Plugin64"
        SUFFIX ".dylib"
        PREFIX ""
    )
endif()

target_include_directories(Plugin64 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(Plugin64 PRIVATE
    platform
    ${Boost_LIBRARIES}
)

# Platform-specific compiler flags
if(MSVC)
    target_compile_options(Plugin64 PRIVATE /W4)
else()
    target_compile_options(Plugin64 PRIVATE -Wall -Wextra)
endif()

# macOS specific settings
if(APPLE)
    set_target_properties(Plugin64 PROPERTIES
        MACOSX_RPATH ON
        BUILD_WITH_INSTALL_RPATH ON
        INSTALL_RPATH "@loader_path"
    )
endif()
