set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

file(GLOB_RECURSE SANDBOX_SOURCES
    src/SandboxApp.cpp
    src/ExampleLayer.cpp
    ${VENDOR_DIR}/ImGuizmo/ImGuizmo.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})
target_include_directories(Sandbox PRIVATE
    ${NEAT_DIR}/include
    ${VENDOR_DIR}
)
target_link_libraries(Sandbox PRIVATE Neat)
set_target_properties(Sandbox PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
)

target_compile_definitions(Sandbox PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG;NT_IMGUI>
    $<$<CONFIG:Release>:NT_RELEASE>
    $<$<CONFIG:Dist>:NT_DIST>
)

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:Sandbox>/SandboxAssets/Resources"
)
