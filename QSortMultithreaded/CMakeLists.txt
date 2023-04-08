cmake_minimum_required(VERSION 3.22)
project(qsort)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_subdirectory(src)

add_executable(demo demo.cpp)
target_link_libraries(demo qsort)

enable_testing()
add_subdirectory(test)