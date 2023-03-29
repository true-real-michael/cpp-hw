cmake_minimum_required(VERSION 3.24)
project(Deadlocks)

set(CMAKE_CXX_STANDARD 20)


include_directories(src)
add_subdirectory(src)


option(ENABLE_TESTS OFF)
#SET(ENABLE_TESTS ON)

message(${ENABLE_TESTS})
if(ENABLE_TESTS)

    enable_testing()
    add_subdirectory(test)

endif()
