file(GLOB_RECURSE SANDBOX_SOURCES
    src/**.cpp
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

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Sandbox/assets
    $<TARGET_FILE_DIR:Sandbox>/assets
)
