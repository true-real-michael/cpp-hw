//
// Created by Mikhail Kiselyov on 12.03.2023.
//

#ifndef DEADLOCKS_ALLOCATIONSIMULATOR_H
#define DEADLOCKS_ALLOCATIONSIMULATOR_H

#include <map>
#include <vector>
#include "Resource.h"
#include "Process.h"

namespace ResourceAllocation {

    bool AllocationIsSafe(std::vector<Resource> resources,
                          std::map<Resource, size_t> newAvailable,
                          std::vector<Process> newProcessState);

} // AllocationSimulator

#endif //DEADLOCKS_ALLOCATIONSIMULATOR_H
