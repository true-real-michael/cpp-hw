project(AllocationSimulatorTests)

add_subdirectory(googletest-lib)
include_directories(${gtest_SOUCE_DIR}/include ${gtest_SOUCE_DIR})

file(GLOB test_sources "*.cpp")
add_executable(run_google_tests ${test_sources})

target_link_libraries(run_google_tests gtest gtest_main)
target_link_libraries(run_google_tests AllocationSimulator)

add_test(run_cTests run_google_tests)
