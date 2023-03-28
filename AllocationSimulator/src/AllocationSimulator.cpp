//
// Created by Mikhail Kiselyov on 12.03.2023.
//

#include "AllocationSimulator.h"

namespace ResourceAllocation {
    bool AllocationIsSafe(std::vector<Resource> resources,
                          std::map<Resource, size_t> newAvailable,
                          std::vector<Process> newProcessState) {

        for (auto &process: newProcessState) {
            if (process.IsFinished()) {
                continue;
            }

            if (std::all_of(resources.begin(), resources.end(),
                            [newAvailable, process](auto resource) {
                                return process.RequestsResource(resource) - process.AllocatedResource(resource) <=
                                       newAvailable.at(resource);
                            })) {

                for (const auto& resource: resources) {
                    newAvailable[resource] += process.AllocatedResource(resource);
                }
                process.Finish();

            } else {
                break;
            }
        }

        return std::all_of(newProcessState.begin(), newProcessState.end(),
                           [](const auto &process) {
                               return process.IsFinished();
                           });
    }

} // AllocationSimulator