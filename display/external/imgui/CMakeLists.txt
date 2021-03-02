project(imgui LANGUAGES CXX)

add_library(${PROJECT_NAME}
    OBJECT
        imgui-SFML.cpp
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
)

set(IMGUI_LIBRARY
        sfml-system
        sfml-system-d
        sfml-main
        sfml-main-d
        sfml-window
        sfml-window-d
        sfml-graphics
        sfml-graphics-d
    CACHE PATH "Imgui-SFML library"
)

set(IMGUI_DLL_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/bin
    CACHE PATH "Imgui-SFML path to all required dll"
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include
)
