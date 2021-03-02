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
        src/gui/cmdtranslator.cpp
        src/gui/cmdtranslator.hpp

        external/concurrentqueue.h

        $<TARGET_OBJECTS:imgui>
)

set(DISPLAY_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE PATH "Path to includes all of dependent libraries for display"
)

set(DISPLAY_LINK_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/SFML/lib
    CACHE PATH "Dispaly library location"
)

set(DISPLAY_LIBRARY
        ${PROJECT_NAME}
        ${IMGUI_LIBRARY}
    CACHE STRING "List of all libraries needed in project using display"
)

set(DISPLAY_DEPENDENCIES_DLL_PATH
       ${IMGUI_DLL_PATH}
    CACHE PATH "Required DLL's path"
)

add_definitions(-DRESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/external
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/SFML/include
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${COMMON_LIBRARY})

target_compile_definitions(display PRIVATE DISPLAY_LIBRARY)
