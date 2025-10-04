cmake_minimum_required(VERSION 3.28)
project(NeatProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist")

add_subdirectory(Neat)
add_subdirectory(NeatEditor)
add_subdirectory(Tests)
add_subdirectory(Examples)
add_subdirectory(Sandbox)

