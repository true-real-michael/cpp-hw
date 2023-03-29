cmake_minimum_required(VERSION 3.22)
project(qsort)

set(CMAKE_CXX_STANDARD 17)

#add_compile_options(-std=c++17 -stdlib=libc++ -lpthread)

add_executable(demo demo.cpp)

include_directories(src)