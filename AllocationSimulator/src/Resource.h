//
// Created by Mikhail Kiselyov on 12.03.2023.
//

#ifndef DEADLOCKS_RESOURCE_H
#define DEADLOCKS_RESOURCE_H

#include <string>

namespace ResourceAllocation {

    class Resource {
        static size_t nextID;
        size_t ID;
        std::string name;
    public:
        Resource();
        Resource(std::string name);

        std::string GetName() const;
        size_t GetID() const;
        bool operator<(const Resource &other) const;
    };

} // AllocationSimulator

#endif //DEADLOCKS_RESOURCE_H
