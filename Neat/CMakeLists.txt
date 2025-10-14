set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

# ImGui
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD -DGLFW_INCLUDE_NONE)

file(GLOB_RECURSE NEAT_SOURCES
    src/Components/**.cpp
    src/Core/**.cpp
    src/Debug/**.cpp
    src/ECS/**.cpp
    src/Events/**.cpp
    src/EventDispatching/**.cpp
    src/Graphics/**.cpp
    src/ImGui/**.cpp
    src/Math/**.cpp
    src/Scene/**.cpp
    src/Systems/**.cpp
    src/Utils/**.cpp

    # Platform specific
    src/Platform/OpenGL/**.cpp

    # Vendor
    ${VENDOR_DIR}/stb_image/stb_image.cpp
    ${VENDOR_DIR}/ImGui/imgui_demo.cpp
    ${VENDOR_DIR}/ImGui/imgui_draw.cpp
    ${VENDOR_DIR}/ImGui/imgui_widgets.cpp
    ${VENDOR_DIR}/ImGui/imgui_tables.cpp
    ${VENDOR_DIR}/ImGui/imgui.cpp
    ${VENDOR_DIR}/ImGui/backends/imgui_impl_glfw.cpp
    ${VENDOR_DIR}/ImGui/backends/imgui_impl_opengl3.cpp
    ${VENDOR_DIR}/ImGuizmo/ImGuizmo.cpp
)

message(STATUS "NEAT_SOURCES: ${NEAT_SOURCES}")

add_library(Neat STATIC ${NEAT_SOURCES})

if(MSVC)
    target_compile_options(Neat PUBLIC
        /utf-8
    )
    target_compile_options(Neat PRIVATE
        /W4
        /permissive-
    )
    # Warnings as errors
    #set_source_files_properties(${NEAT_SOURCES} PROPERTIES
    #    COMPILE_OPTIONS "$<$<CONFIG:Debug>:/WX>"
    #)
else()
    target_compile_options(Neat PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
    set_source_files_properties(${NEAT_SOURCES} PROPERTIES
        COMPILE_OPTIONS "$<$<CONFIG:Debug>:-Werror>"
    )
endif()

target_precompile_headers(Neat PRIVATE
    src/NeatPCH.hpp
)

target_include_directories(Neat PUBLIC src)

# Use SYSTEM to suppress warnings from external headers to be treated as errors
target_include_directories(Neat
    SYSTEM PUBLIC
        ${VENDOR_DIR}/GLFW/include
        ${VENDOR_DIR}/Glad/include
        ${VENDOR_DIR}/ImGui
        ${VENDOR_DIR}/spdlog/include
        ${VENDOR_DIR}/stb_image
        ${VENDOR_DIR}/reflect-cpp/include
        ${VENDOR_DIR}/yaml-cpp/include
        ${VENDOR_DIR}/ImGuizmo
        ${VENDOR_DIR}/Box2D/include
)

set(PUBLIC_LIBRARIES
    glfw
    Glad
    yaml-cpp
    reflectcpp
    box2d)

if(WIN32)
    set(PUBLIC_LIBRARIES ${PUBLIC_LIBRARIES} opengl32.lib)
elseif(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    find_package(Threads REQUIRED)
    set(PUBLIC_LIBRARIES ${PUBLIC_LIBRARIES} OpenGL::GL pthread dl X11::X11 ${CMAKE_THREAD_LIBS_INIT})
endif()

target_link_libraries(Neat PUBLIC ${PUBLIC_LIBRARIES})

target_compile_definitions(Neat PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG;NT_IMGUI>
    $<$<CONFIG:Release>:NT_RELEASE>
    $<$<CONFIG:Dist>:NT_DIST>
)

set_target_properties(Neat PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
)

add_custom_command(TARGET Neat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:Neat>/NeatAssets/Resources"
)
