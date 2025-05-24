cmake_minimum_required(VERSION 3.28)
project(NeatProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(OUTPUT_INT_DIR "${CMAKE_BINARY_DIR}/bin-int/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist")

# Dependencies
add_subdirectory(Neat/vendor/GLFW)
add_subdirectory(Neat/vendor/Glad)

# Projects
add_subdirectory(Neat)
add_subdirectory(Sandbox)
add_subdirectory(Tests)