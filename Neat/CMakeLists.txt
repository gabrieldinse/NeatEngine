
add_subdirectory(vendor)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD -DGLFW_INCLUDE_NONE)

file(GLOB_RECURSE NEAT_SOURCES
    src/Neat/**.cpp
    src/Platform/OpenGL/**.cpp
    vendor/stb_image/stb_image.cpp
    vendor/ImGui/imgui_demo.cpp
    vendor/ImGui/imgui_draw.cpp
    vendor/ImGui/imgui_widgets.cpp
    vendor/ImGui/imgui_tables.cpp
    vendor/ImGui/imgui.cpp
    vendor/ImGui/backends/imgui_impl_glfw.cpp
    vendor/ImGui/backends/imgui_impl_opengl3.cpp
)

file(GLOB_RECURSE LINUX_SOURCES
    src/Platform/Linux/**.cpp
)

if(WIN32)

elseif(UNIX AND NOT APPLE)
    set(NEAT_SOURCES ${NEAT_SOURCES} ${LINUX_SOURCES})
endif()

message(STATUS "NEAT_SOURCES: ${NEAT_SOURCES}")

add_library(Neat STATIC ${NEAT_SOURCES})

target_compile_options(Neat PRIVATE
    -Wall -Wextra -Wpedantic
    $<$<CONFIG:Debug>:-Werror>
)

target_precompile_headers(Neat PRIVATE
    src/NeatPCH.hpp
)

target_include_directories(Neat PUBLIC
    src
    vendor/GLFW/include
    vendor/Glad/include
    vendor/ImGui
    vendor/spdlog/include
    vendor/stb_image
)

set(LIBS glfw Glad)

if(WIN32)
    set(LIBS ${LIBS} opengl32.lib)
elseif(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    find_package(Threads REQUIRED)
    set(LIBS ${LIBS} OpenGL::GL pthread dl X11::X11 ${CMAKE_THREAD_LIBS_INIT})
endif()

target_link_libraries(Neat PUBLIC ${LIBS})

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

file(COPY ${CMAKE_SOURCE_DIR}/Resources DESTINATION ${OUTPUT_DIR})