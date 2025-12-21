add_library(platform STATIC
    platform.cpp
    platform.h
)

target_include_directories(platform PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(APPLE)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation REQUIRED)
    target_link_libraries(platform PUBLIC ${COREFOUNDATION_LIBRARY})
endif()
