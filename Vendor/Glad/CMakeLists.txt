# Glad - CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Glad LANGUAGES C)

# Set output directories similar to premake
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/$<CONFIG>-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

# Source files
set(GLAD_SOURCES
    src/glad.c
)

# Header files (not needed for compilation but good to list)
set(GLAD_HEADERS
    include/glad/glad.h
    include/KHR/khrplatform.h
)

# Create static library
add_library(Glad STATIC ${GLAD_SOURCES})

# Include directories
target_include_directories(Glad PUBLIC include)

# Compile definitions
target_compile_definitions(Glad PRIVATE GLAD_GL_IMPLEMENTATION)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Configuration-specific settings
set_target_properties(Glad PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/$<0:>
)

# Installation (optional)
install(TARGETS Glad
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)