project(imgui LANGUAGES CXX)

add_library(${PROJECT_NAME}
    OBJECT
        backends/imgui_impl_opengl3.cpp
        backends/imgui_impl_opengl3.h

        glad/include/KHR/khrplatform.h
        glad/include/glad/glad.h
        glad/src/glad.c

        imconfig-SFML.h
        imconfig.h
        imgui-SFML.cpp
        imgui-SFML.h
        imgui-SFML_export.h
        imgui.cpp
        imgui.h
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_internal.h
        imgui_tables.cpp
        imgui_widgets.cpp
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h

        misc/cpp/imgui_stdlib.cpp
        misc/cpp/imgui_stdlib.h
        misc/fonts/binary_to_compressed_c.cpp
#        misc/freetype/imgui_freetype.cpp
#        misc/freetype/imgui_freetype.h
        misc/single_file/imgui_single_file.h
)

set(IMGUI_LIBRARY
        ${PROJECT_NAME}
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

set(IMGUI_LINK_DIRECTORY
        ${CMAKE_CURRENT_BINARY_DIR}
    CACHE PATH "Path to imgui related build")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
)
