//
// Created by Mikhail Kiselyov on 12.03.2023.
//

#include "Process.h"
#include <exception>

namespace ResourceAllocation {

    size_t Process::nextPID = 0;

    Process::Process(std::map<Resource, size_t> _requestedResources) :
            requestedResources(std::move(_requestedResources)),
            PID(nextPID++) {
        for (const auto &request: requestedResources) {
            allocatedResources[request.first] = 0;
        }
    }

    Process::Process(std::map<Resource, size_t> _requestedResources, std::map<Resource, size_t> _allocatedResources) :
            requestedResources(std::move(_requestedResources)),
            allocatedResources(std::move(_allocatedResources)),
            PID(nextPID++) {}

    void Process::changeResourceAllocation(Resource resource, size_t newAllocation) {
        if (isFinished) {
            throw std::invalid_argument("the process is already finished");
        }
        allocatedResources[resource] = newAllocation;
    }

    bool Process::IsFinished() const {
        return isFinished;
    }

    size_t Process::GetPID() const {
        return PID;
    }

    bool Process::operator<(const Process &other) const {
        return PID < other.GetPID();
    }

    size_t Process::RequestsResource(Resource resource) const {
        return requestedResources.find(resource) == requestedResources.end() ? 0 : requestedResources.at(resource);
    }

    size_t Process::AllocatedResource(Resource resource) const {
        return allocatedResources.find(resource) == allocatedResources.end() ? 0 : allocatedResources.at(resource);
    }

    void Process::Finish() {
        isFinished = true;
    }

} // AllocationSimulator