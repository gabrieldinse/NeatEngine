file(GLOB_RECURSE NEAT_EDIT_SOURCES
    src/**.cpp
)

add_executable(NeatEditor ${NEAT_EDIT_SOURCES})
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

target_compile_options(NeatEditor PRIVATE
    -Wall -Wextra -Wpedantic
    $<$<CONFIG:Debug>:-Werror -O0>
)

target_compile_definitions(NeatEditor PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG;NT_IMGUI>
    $<$<CONFIG:Release>:NT_RELEASE>
    $<$<CONFIG:Dist>:NT_DIST>
)

file(COPY assets DESTINATION ${OUTPUT_DIR})