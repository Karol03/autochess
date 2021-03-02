project(board LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME}
    STATIC
        board.cpp
        board.hpp
)

set(BOARD_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE PATH "Path to board includes"
)

set(BOARD_LIBRARY
        ${PROJECT_NAME}
    CACHE STRING "Board libraries list"
)

set(BOARD_LINK_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
    CACHE PATH "Board directory link"
)

target_compile_definitions(board PRIVATE BOARD_LIBRARY)
