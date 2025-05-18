cmake_minimum_required(VERSION 3.10)
project(NeatProject)

# Set OpenGL policy
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

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
#set(GLAD_SOURCES Neat/vendor/Glad/src/glad.c)
#add_library(Glad STATIC ${GLAD_SOURCES})
target_include_directories(Glad PUBLIC Neat/vendor/Glad/include)
#target_compile_definitions(Glad PRIVATE GLAD_GL_IMPLEMENTATION)

# ImGui (custom setup)
#file(GLOB IMGUI_SOURCES
#    Neat/vendor/ImGui/*.cpp
#    Neat/vendor/ImGui/*.h
#)
#add_library(ImGui STATIC ${IMGUI_SOURCES})
#target_include_directories(ImGui PUBLIC Neat/vendor/ImGui)

#-------------------------------------------------------------------------------
# Neat Library
#-------------------------------------------------------------------------------
file(GLOB_RECURSE ALL_SOURCES
    Neat/src/Neat/**.h
    Neat/src/Neat/**.hpp
    Neat/src/Neat/**.cpp
    Neat/src/Neat/**.inl
    Neat/src/*.h
    Neat/src/*.hpp
    Neat/src/*.cpp
    Neat/vendor/stb_image/**.h
    Neat/vendor/stb_image/**.cpp
)

# TODO remove this
foreach(file ${ALL_SOURCES})
    if(NOT file MATCHES ".*/ImGui/.*")
        list(APPEND NEAT_SOURCES ${file})
    endif()
endforeach()

if(WIN32)
    file(GLOB_RECURSE NEAT_PLATFORM_SOURCES
        Neat/src/Platform/Windows/**.h
        Neat/src/Platform/Windows/**.hpp
        Neat/src/Platform/Windows/**.cpp
    )
    list(APPEND NEAT_SOURCES ${NEAT_PLATFORM_SOURCES})
    add_definitions(-DGLFW_INCLUDE_NONE)
endif()

if(UNIX AND NOT APPLE)  # Linux
    # Add Linux platform sources
    file(GLOB_RECURSE LINUX_SOURCES
        Neat/src/Platform/Linux/**.h
        Neat/src/Platform/Linux/**.hpp
        Neat/src/Platform/Linux/**.cpp
    )
    add_definitions(-DGLFW_INCLUDE_NONE)
    list(APPEND NEAT_SOURCES ${LINUX_SOURCES})
endif()

add_library(Neat STATIC ${NEAT_SOURCES})

target_include_directories(Neat PUBLIC
    Neat/src
    Neat/vendor/GLFW/include
    Neat/vendor/Glad/include
    Neat/vendor/ImGui
    Neat/vendor/spdlog/include
    Neat/vendor/stb_image
)

#target_link_libraries(Neat PRIVATE GLFW Glad ImGui)
target_link_libraries(Neat PRIVATE glfw Glad)

find_package(OpenGL REQUIRED)
if(WIN32)
    target_link_libraries(Neat PRIVATE opengl32.lib)
else()
    target_link_libraries(Neat PRIVATE OpenGL::GL)
    target_link_libraries(Neat PRIVATE pthread dl)
    if(UNIX AND NOT APPLE)
        # Moved Linux-specific linking here
        find_package(X11 REQUIRED)
        find_package(Threads REQUIRED)
        target_link_libraries(Neat PRIVATE 
            X11::X11
            ${CMAKE_THREAD_LIBS_INIT}
        )
    endif()
endif()

# Configuration settings
target_compile_definitions(Neat
    PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG>
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
    Neat/vendor/spdlog/include
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