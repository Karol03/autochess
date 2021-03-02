project(common LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME}
    STATIC
        logger.cpp
        logger.hpp

        logsource/stream.hpp
        logsource/stringlog.cpp
        logsource/stringlog.hpp
)

set(COMMON_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE PATH "Path to includes all of dependent libraries for common"
)

set(COMMON_LIBRARY
        ${PROJECT_NAME}
    CACHE STRING "List of all libraries needed in project using common library"
)

set(COMMON_LINK_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
    CACHE PATH "Common library location"
)

target_compile_definitions(common PUBLIC COMMON_LIBRARY)
