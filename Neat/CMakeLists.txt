add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD -DGLFW_INCLUDE_NONE)

file(GLOB_RECURSE NEAT_SOURCES
    src/Neat/**.cpp
    src/*.cpp
    vendor/stb_image/**.cpp
    vendor/ImGui/imgui_demo.cpp
    vendor/ImGui/imgui_draw.cpp
    vendor/ImGui/imgui_widgets.cpp
    vendor/ImGui/imgui_tables.cpp
    vendor/ImGui/imgui.cpp
    vendor/ImGui/backends/imgui_impl_glfw.cpp
    vendor/ImGui/backends/imgui_impl_opengl3.cpp
)

message(STATUS "NEAT_SOURCES: ${NEAT_SOURCES}")

if(UNIX AND NOT APPLE)
    file(GLOB_RECURSE LINUX_SOURCES
        src/Platform/Linux/**.cpp
    )
    list(APPEND NEAT_SOURCES ${LINUX_SOURCES})
endif()

add_library(Neat STATIC ${NEAT_SOURCES})

target_include_directories(Neat PUBLIC
    src
    vendor/GLFW/include
    vendor/Glad/include
    vendor/ImGui
    vendor/spdlog/include
    vendor/stb_image
)

target_link_libraries(Neat PUBLIC glfw Glad)

find_package(OpenGL REQUIRED)
if(WIN32)
    target_link_libraries(Neat PUBLIC opengl32.lib)
else()
    target_link_libraries(Neat PUBLIC OpenGL::GL pthread dl)
    if(UNIX AND NOT APPLE)
        find_package(X11 REQUIRED)
        find_package(Threads REQUIRED)
        target_link_libraries(Neat PUBLIC X11::X11 ${CMAKE_THREAD_LIBS_INIT})
    endif()
endif()

target_compile_definitions(Neat PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG;NT_IMGUI>
    $<$<CONFIG:Release>:NT_RELEASE>
    $<$<CONFIG:Dist>:NT_DIST>
)

set_target_properties(Neat PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)
