file(GLOB_RECURSE NEAT_EDITOR_SOURCES
    src/**.cpp
)

# Add ImGuiFileDialog source file sepparate to not have -Werror on it
add_executable(NeatEditor
    ${NEAT_EDITOR_SOURCES}
    ../Neat/vendor/ImGuiFileDialog/ImGuiFileDialog.cpp
    ../Neat/vendor/ImGuizmo/ImGuizmo.cpp
)

target_compile_options(NeatEditor PRIVATE
    -Wall -Wextra -Wpedantic
)

set_source_files_properties(${NEAT_EDITOR_SOURCES} PROPERTIES
    COMPILE_OPTIONS "$<$<CONFIG:Debug>:-Werror>"
)

target_include_directories(NeatEditor PRIVATE
    ../Neat/src
    ../Neat/vendor
)
target_link_libraries(NeatEditor PRIVATE Neat)
set_target_properties(NeatEditor PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_compile_definitions(NeatEditor PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG;NT_IMGUI>
    $<$<CONFIG:Release>:NT_RELEASE>
    $<$<CONFIG:Dist>:NT_DIST>
)

file(COPY Assets DESTINATION ${OUTPUT_DIR})
file(COPY imgui.ini DESTINATION ${OUTPUT_DIR})