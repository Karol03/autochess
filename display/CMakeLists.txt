project(display LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common)

add_subdirectory(external)

add_library(${PROJECT_NAME}
    STATIC
        displayapi.hpp

        displayhandler.hpp
        movestream.hpp
        onboardconfig.hpp
        onboardmove.hpp

        src/display.cpp
        src/display.hpp
        src/displayhandler.cpp
        src/configtranslator.cpp
        src/configtranslator.hpp
        src/movetranslator.cpp
        src/movetranslator.hpp
        src/onboardconfig.cpp
        src/onboardmove.cpp
        src/pieces.cpp
        src/pieces.hpp
        src/piecesmap.hpp
        src/piecetype.hpp
        src/streamitem.hpp
        src/window.cpp
        src/window.hpp

        src/gui/console.cpp
        src/gui/console.hpp
        src/gui/gui.cpp
        src/gui/gui.hpp

        external/concurrentqueue.h

        $<TARGET_OBJECTS:imgui>
)

set(DISPLAY_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/displayapi.hpp
    CACHE PATH "Path to includes all of dependent libraries for display"
)

set(DISPLAY_LINK_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/SFML/lib
        ${IMGUI_LINK_DIRECTORY}
    CACHE PATH "Dispaly library location"
)

set(DISPLAY_LIBRARY
        ${PROJECT_NAME}
    CACHE STRING "List of all libraries needed in project using display"
)

add_definitions(-DRESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources")

target_compile_definitions(display PRIVATE DISPLAY_LIBRARY)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/external
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/SFML/include
)
