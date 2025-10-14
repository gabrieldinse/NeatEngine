
enable_testing()

# Add GoogleTest
add_subdirectory(${VENDOR_DIR}/GoogleTest ${CMAKE_BINARY_DIR}/GoogleTest-build)

# Collect test files
file(
    GLOB_RECURSE
    NEAT_TESTS_SOURCES
    src/*.cpp
)

# Build the test executable
add_executable(NeatTests ${NEAT_TESTS_SOURCES})
add_dependencies(NeatTests Neat)

if(MSVC)
    target_compile_options(NeatTests PRIVATE
        /W4
        /permissive-
    )
    # TODO uncomment
    #set_source_files_properties(${NEAT_EDITOR_SOURCES} PROPERTIES
    #    COMPILE_OPTIONS "$<$<CONFIG:Debug>:/WX>"
    #)
else()
    target_compile_options(NeatTests PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
    set_source_files_properties(${NEAT_TESTS_SOURCES} PROPERTIES
        COMPILE_OPTIONS "$<$<CONFIG:Debug>:-Werror>"
    )
endif()

# Include headers
target_include_directories(NeatTests PUBLIC
    ${NEAT_DIR}/src
    src
)

# Link against Neat and GoogleTest
target_link_libraries(
    NeatTests
    GTest::gtest_main
    Neat
)

# Automatically run tests when building
add_test(NAME AllTests COMMAND NeatTests)

add_custom_command(TARGET NeatTests POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose
)