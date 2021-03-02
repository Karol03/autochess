cmake_minimum_required(VERSION 3.14)

project(chess LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_LIBRARIES "-lglu32 -lopengl32 -loleaut32 -limm32 -lversion -lole32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_CXX_FLAGS_DEBUG "-fno-inline -O0 -g -ggdb -Wall -Werror -pedantic -static -static-libgcc -static-libstdc++ -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive ")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -pedantic -Werror -pedantic -static -static-libgcc -static-libstdc++ -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/board)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/display)


add_executable(${PROJECT_NAME}
    main.cpp
)

message("Include directories: ${COMMON_INCLUDES};${BOARD_INCLUDES};${DISPLAY_INCLUDES}")
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${COMMON_INCLUDES}
        ${BOARD_INCLUDES}
        ${DISPLAY_INCLUDES}
)

message("Add link directories: ${COMMON_LINK_DIRECTORY};${BOARD_LINK_DIRECTORY};${DISPLAY_LINK_DIRECTORY}")
target_link_directories(${PROJECT_NAME}
    PUBLIC
        ${COMMON_LINK_DIRECTORY}
        ${BOARD_LINK_DIRECTORY}
        ${DISPLAY_LINK_DIRECTORY}
)

message("Link libraries: ${COMMON_LIBRARY};${BOARD_LIBRARY};${DISPLAY_LIBRARY}")
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${COMMON_LIBRARY}
        ${BOARD_LIBRARY}
        ${DISPLAY_LIBRARY}
)


message("Copy DLL's to destination directory")
file(GLOB DLLS
    ${DISPLAY_DEPENDENCIES_DLL_PATH}/*.dll
)
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
    ${DLLS}
    ${CMAKE_CURRENT_BINARY_DIR})
