project(common LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME}
    STATIC
        variableevent.hpp
        variableevent.cpp
)

set(COMMON_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE PATH "Path to common includes"
)

set(COMMON_LIBRARY
        ${PROJECT_NAME}
    CACHE STRING "Libraries list"
)

set(COMMON_LINK_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
    CACHE PATH "Directory link"
)
