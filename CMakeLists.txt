cmake_minimum_required(VERSION 3.14)

project(chess LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_LIBRARIES "-lglu32 -lopengl32 -loleaut32 -limm32 -lversion -lole32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_CXX_FLAGS_DEBUG "-fno-inline -O0 -g -ggdb -Wall -Werror -pedantic -static -static-libgcc -static-libstdc++ -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -pedantic -Werror -pedantic -static-libgcc -static-libstdc++ -lstdc++ ")
#set(CMAKE_CXX_STANDARD_LIBRARIES "-static -static-libgcc -static-libstdc++ -lwinpthread ${CMAKE_CXX_STANDARD_LIBRARIES}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
#set(CMAKE_CXX_FLAGS_DEBUG "-fno-inline -O0 -g -ggdb -Wall -Werror -pedantic")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -pedantic -Werror -pedantic")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/board)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/display)

message("Include directories: ${BOARD_INCLUDES};${DISPLAY_INCLUDES}")
include_directories(
        ${BOARD_INCLUDES}
        ${DISPLAY_INCLUDES}
)


message("Add link directories: ${BOARD_LINK_DIRECTORY};${DISPLAY_LINK_DIRECTORY}")
link_directories(
        ${BOARD_LINK_DIRECTORY}
        ${DISPLAY_LINK_DIRECTORY}
        ${COMMON_LINK_DIRECTORY}
)


message("Link for board: ${BOARD_LIBRARY};${DISPLAY_LIBRARY}")
link_libraries(
        ${BOARD_LIBRARY}
        ${DISPLAY_LIBRARY}
        ${COMMON_LIBRARY}
)

add_executable(${PROJECT_NAME}
    main.cpp
)
