file(GLOB_RECURSE FLAPPY_SOURCES src/**.cpp)

add_executable(FlappySpaceship ${FLAPPY_SOURCES})

target_include_directories(FlappySpaceship PRIVATE
    ../../Neat/src
    ../../Neat/vendor
)
target_link_libraries(FlappySpaceship PRIVATE Neat)

set_target_properties(FlappySpaceship PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

target_compile_definitions(FlappySpaceship PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG;NT_IMGUI>
    $<$<CONFIG:Release>:NT_RELEASE>
    $<$<CONFIG:Dist>:NT_DIST>
)
file(COPY assets DESTINATION ${OUTPUT_DIR})
