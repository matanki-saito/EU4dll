# Plugin (32-bit Windows only)
# This is only built on Windows platforms

set(PLUGIN_SOURCES
    ButtonAndToolTip.cpp
    DateFormat.cpp
    IME.cpp
    FileSave.cpp
    InputIssue19.cpp
    ListChars.cpp
    Input.cpp
    NameOrder.cpp
    ToolTipApx.cpp
    Popup.cpp
    ShowFileName.cpp
    Text.cpp
    byte_pattern.cpp
    dllmain.cpp
    eventDialog.cpp
    font.cpp
    mapAdj.cpp
    mapJustify.cpp
    mapView.cpp
    misc.cpp
    moddl.cpp
    version.cpp
)

set(PLUGIN_HEADERS
    byte_pattern.h
    moddl.h
    stdinc.h
)

add_library(Plugin SHARED
    ${PLUGIN_SOURCES}
    ${PLUGIN_HEADERS}
)

set_target_properties(Plugin PROPERTIES
    OUTPUT_NAME "Plugin"
    SUFFIX ".dll"
)

target_include_directories(Plugin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(Plugin PRIVATE
    platform
    ${Boost_LIBRARIES}
)

if(MSVC)
    target_compile_options(Plugin PRIVATE /W4)
endif()
