set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

file(GLOB_RECURSE NEAT_EDITOR_SOURCES
    src/**.cpp
)

# Add ImGuiFileDialog source file sepparate to not have -Werror on it
add_executable(NeatEditor
    ${NEAT_EDITOR_SOURCES}
    ${VENDOR_DIR}/ImGuiFileDialog/ImGuiFileDialog.cpp
)

target_compile_options(NeatEditor PRIVATE
    -Wall -Wextra -Wpedantic
)

set_source_files_properties(${NEAT_EDITOR_SOURCES} PROPERTIES
    COMPILE_OPTIONS "$<$<CONFIG:Debug>:-Werror>"
)

target_include_directories(NeatEditor PRIVATE
    ${NEAT_DIR}/src
    ${VENDOR_DIR}
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

file(COPY Resources DESTINATION ${OUTPUT_DIR}/NeatEditorAssets)
file(COPY imgui.ini DESTINATION ${OUTPUT_DIR})
