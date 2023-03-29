//
// Created by Mikhail Kiselyov on 12.03.2023.
//

#ifndef DEADLOCKS_PROCESS_H
#define DEADLOCKS_PROCESS_H

#include <map>
#include "Resource.h"

namespace ResourceAllocation {

    class Process {
        static size_t nextPID;

        size_t PID;
        std::map<Resource, size_t> requestedResources;
        std::map<Resource, size_t> allocatedResources;
        bool isFinished = false;

    public:
        explicit Process(std::map<Resource, size_t> _requestedResources);
        Process(std::map<Resource, size_t> _requestedResources,
                std::map<Resource, size_t> _allocatedResources);

        void Finish();
        void changeResourceAllocation(Resource resource, size_t newAllocation);

        bool IsFinished() const;
        size_t RequestsResource(Resource resource) const;
        size_t AllocatedResource(Resource resource) const;

        size_t GetPID() const;
        bool operator<(const Process &other) const;
    };

} // AllocationSimulator

#endif //DEADLOCKS_PROCESS_H
