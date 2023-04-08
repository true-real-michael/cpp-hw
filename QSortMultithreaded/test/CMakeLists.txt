project(multithreadedQSortTest)

find_package(GTest CONFIG REQUIRED)

add_executable(speed_test SpeedTest.cpp)

target_link_libraries(speed_test GTest::gtest GTest::gtest_main)
target_link_libraries(speed_test qsort)

add_test(Test speed_test)