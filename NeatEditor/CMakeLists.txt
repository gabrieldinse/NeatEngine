set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

file(GLOB_RECURSE NEAT_EDITOR_SOURCES
    src/**.cpp
)

# Add ImGuiFileDialog source file sepparate to not have -Werror on it
add_executable(NeatEditor
    ${NEAT_EDITOR_SOURCES}
    ${VENDOR_DIR}/ImGuiFileDialog/ImGuiFileDialog.cpp
)

if(MSVC)
    target_compile_options(NeatEditor PRIVATE
        /W4
        /permissive-
    )
    # TODO uncomment
    #set_source_files_properties(${NEAT_EDITOR_SOURCES} PROPERTIES
    #    COMPILE_OPTIONS "$<$<CONFIG:Debug>:/WX>"
    #)
else()
    target_compile_options(NeatEditor PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
    set_source_files_properties(${NEAT_EDITOR_SOURCES} PROPERTIES
        COMPILE_OPTIONS "$<$<CONFIG:Debug>:-Werror>"
    )
endif()

target_include_directories(NeatEditor PRIVATE
    ${NEAT_DIR}/src
    ${NEAT_DIR}/include
    ${VENDOR_DIR}
)
target_link_libraries(NeatEditor PRIVATE Neat)
set_target_properties(NeatEditor PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
)

target_compile_definitions(NeatEditor PRIVATE
    $<$<CONFIG:Debug>:NT_DEBUG;NT_IMGUI>
    $<$<CONFIG:Release>:NT_RELEASE>
    $<$<CONFIG:Dist>:NT_DIST>
)

add_custom_command(TARGET NeatEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:NeatEditor>/NeatEditorAssets/Resources"
)
add_custom_command(TARGET NeatEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini"
        "$<TARGET_FILE_DIR:NeatEditor>/imgui.ini"
)
