cmake_minimum_required(VERSION 3.28)
project(NeatProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(OUTPUT_INT_DIR "${CMAKE_BINARY_DIR}/bin-int/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

# Configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist")

#-------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------

# GLFW
add_subdirectory(Neat/vendor/GLFW)

# GLAD (custom setup)
add_subdirectory(Neat/vendor/Glad)
target_include_directories(Glad PUBLIC Neat/vendor/Glad/include)

#-------------------------------------------------------------------------------
# Neat Library
#-------------------------------------------------------------------------------
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)
file(GLOB_RECURSE NEAT_SOURCES
    Neat/src/Neat/**.cpp
    Neat/src/*.cpp
    Neat/vendor/stb_image/**.h
    Neat/vendor/stb_image/**.cpp
    Neat/vendor/ImGui/imgui_demo.cpp
    Neat/vendor/ImGui/imgui_draw.cpp
    Neat/vendor/ImGui/imgui_widgets.cpp
    Neat/vendor/ImGui/imgui_tables.cpp
    Neat/vendor/ImGui/imgui.cpp
    Neat/vendor/ImGui/backends/imgui_impl_glfw.cpp
    Neat/vendor/ImGui/backends/imgui_impl_opengl3.cpp
)

if(UNIX AND NOT APPLE)  # Linux
    # Add Linux platform sources
    file(GLOB_RECURSE LINUX_SOURCES
        Neat/src/Platform/Linux/**.hpp
        Neat/src/Platform/Linux/**.cpp
    )
    list(APPEND NEAT_SOURCES ${LINUX_SOURCES})
endif()

add_definitions(-DGLFW_INCLUDE_NONE)
add_library(Neat STATIC ${NEAT_SOURCES})

target_include_directories(Neat PUBLIC
    Neat/src
    Neat/vendor/GLFW/include
    Neat/vendor/Glad/include
    Neat/vendor/ImGui
    Neat/vendor/spdlog/include
    Neat/vendor/stb_image
)

target_link_libraries(Neat PUBLIC glfw Glad)

find_package(OpenGL REQUIRED)
if(WIN32)
    target_link_libraries(Neat PUBLIC opengl32.lib)
else()
    target_link_libraries(Neat PUBLIC OpenGL::GL)
    target_link_libraries(Neat PUBLIC pthread dl)
    if(UNIX AND NOT APPLE)
        # Moved Linux-specific linking here
        find_package(X11 REQUIRED)
        find_package(Threads REQUIRED)
        target_link_libraries(Neat PUBLIC 
            X11::X11
            ${CMAKE_THREAD_LIBS_INIT}
        )
    endif()
endif()

# Configuration settings
target_compile_definitions(Neat
    PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG;NT_IMGUI>
    $<$<CONFIG:Release>:NT_RELEASE>
    $<$<CONFIG:Dist>:NT_DIST>
)

#-------------------------------------------------------------------------------
# Sandbox Executable
#-------------------------------------------------------------------------------
file(GLOB_RECURSE SANDBOX_SOURCES
    Sandbox/src/**.h
    Sandbox/src/**.hpp
    Sandbox/src/**.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})
target_include_directories(Sandbox PRIVATE
    Neat/src
    Neat/vendor
)
target_link_libraries(Sandbox PRIVATE Neat)

# Set output directories
set_target_properties(Neat Sandbox PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

# This was necessary when compiling on Linux for Renderer2D. On Windows, the
# path was found for some reason
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Sandbox/assets
    $<TARGET_FILE_DIR:Sandbox>/assets
)