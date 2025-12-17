cmake_minimum_required(VERSION 3.10)
project(GraphProject)

set(CMAKE_SUPPRESS_REGENERATION true)

# Set C++ standard (recommended)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your executable
add_executable(graph data_structures/Graphs/graph.cpp)

# Tell CMake where to find Eigen headers
target_include_directories(graph PRIVATE "C:/libs/eigen")