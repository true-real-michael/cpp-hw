project(ResourceAllocationSimulator)

set(CMAKE_CXX_STANDARD 20)

add_library(AllocationSimulator
        AllocationSimulator.h
        AllocationSimulator.cpp
        Process.h
        Process.cpp
        Resource.h
        Resource.cpp)