
enable_testing()

# Add GoogleTest
add_subdirectory(${VENDOR_DIR}/GoogleTest ${CMAKE_BINARY_DIR}/GoogleTest-build)

# Collect test files
file(
    GLOB_RECURSE
    NEAT_TESTS_SOURCES

    src/**.cpp

    # Unit tests
    src/Unit/Core/**.cpp
    src/Unit/ECS/**.cpp
    src/Unit/EventDispatching/**.cpp
    src/Unit/Math/**.cpp
    src/Unit/Utils/**.cpp
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

add_test(NAME AllTests COMMAND NeatTests)