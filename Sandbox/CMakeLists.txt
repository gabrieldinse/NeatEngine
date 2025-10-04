set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

file(GLOB_RECURSE SANDBOX_SOURCES
    src/SandboxApp.cpp
    src/ExampleLayer.cpp
    ../Neat/vendor/ImGuizmo/ImGuizmo.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})
target_include_directories(Sandbox PRIVATE
    ../Neat/src
    ../Neat/vendor
)
target_link_libraries(Sandbox PRIVATE Neat)
set_target_properties(Sandbox PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_compile_definitions(Sandbox PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG;NT_IMGUI>
    $<$<CONFIG:Release>:NT_RELEASE>
    $<$<CONFIG:Dist>:NT_DIST>
)

file(COPY Resources DESTINATION ${OUTPUT_DIR}/SandboxAssets)
