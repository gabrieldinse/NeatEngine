
enable_testing()


# Add GoogleTest (vendored)
add_subdirectory(../Neat/vendor/GoogleTest ${CMAKE_BINARY_DIR}/GoogleTest-build)

# Collect test files
file(
    GLOB_RECURSE
    TEST_SOURCES
    src/*.cpp
)

# Build the test executable
add_executable(NeatTests ${TEST_SOURCES})

# Include headers
target_include_directories(NeatTests PUBLIC
    ../Neat/src
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