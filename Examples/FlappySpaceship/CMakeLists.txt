set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

file(GLOB_RECURSE FLAPPY_SOURCES src/**.cpp)

add_executable(FlappySpaceship ${FLAPPY_SOURCES})

target_include_directories(FlappySpaceship PRIVATE
    ${NEAT_DIR}/src
    ${VENDOR_DIR}
)
target_link_libraries(FlappySpaceship PRIVATE Neat)

set_target_properties(FlappySpaceship PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
)

target_compile_definitions(FlappySpaceship PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG;NT_IMGUI>
    $<$<CONFIG:Release>:NT_RELEASE>
    $<$<CONFIG:Dist>:NT_DIST>
)

add_custom_command(TARGET FlappySpaceship POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:FlappySpaceship>/FlappySpaceshipAssets/Resources"
)