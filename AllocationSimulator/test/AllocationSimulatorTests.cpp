//
// Created by Mikhail Kiselyov on 12.03.2023.
//

#include "gtest/gtest.h"
#include <map>
#include <vector>
#include "AllocationSimulator.h"

using namespace ResourceAllocation;


// THIS IS AN EXAMPLE OF A DEADLOCK SITUATION
TEST(AllocationSimulationSuite, Invalid) {
    std::vector<Resource> resources({{"A"},  // two types of resources are available
                                     {"B"}});
    std::map<Resource, size_t> availableResources({{resources[0], 0}, // 0 units of A are currently free
                                                   {resources[1], 0}});  // 0 units of B are currently free

    Process proc1({{resources[0], 2},  // proc1 requests total of 2 units of A and 2 units of B
                   {resources[1], 2}},
                  {{resources[0], 2},  // 2 units of A are already allocated to proc1
                   {resources[1], 0}});

    Process proc2({{resources[0], 2},  // proc2 requests total of 2 units of A and 2 units of B
                   {resources[1], 2}},
                  {{resources[0], 0},
                   {resources[1], 2}});// 2 units of B are already allocated to proc1

    // proc1 waits for proc2 to free 2 of B
    // proc2 waits for proc1 to free 2 of A
    // this is a deadlock

    ASSERT_EQ(false, AllocationIsSafe(resources,
                                      availableResources,
                                      {proc1, proc2}));
}


// THIS IS AN EXAMPLE OF AN ABSENCE OF A DEADLOCK
TEST(AllocationSimulationSuite, Valid) {
    std::vector<Resource> resources({{"A"},  // two types of resources are available
                                     {"B"}});
    std::map<Resource, size_t> availableResources({{resources[0], 0}, // 0 units of A are currently free
                                                   {resources[1], 2}});  // 2(!) units of B are currently free

    Process proc1({{resources[0], 2},  // proc1 requests total of 2 units of A and 2 units of B
                   {resources[1], 2}},
                  {{resources[0], 2},  // 2 units of A are already allocated to proc1
                   {resources[1], 0}});

    Process proc2({{resources[0], 2},  // proc2 requests total of 2 units of A and 2 units of B
                   {resources[1], 2}},
                  {{resources[0], 0},
                   {resources[1], 2}});// 2 units of B are already allocated to proc1

    // the deadlock can be avoided if 2 of B is allocated to proc1
    // the process then finishes and frees 2 of B and 2 of A
    // then 2 of A are allocated to proc2
    // proc2 then finishes

    ASSERT_EQ(true, AllocationIsSafe(resources,
                                     availableResources,
                                     {proc1, proc2}));
}
