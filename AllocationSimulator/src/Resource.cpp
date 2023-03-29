//
// Created by Mikhail Kiselyov on 12.03.2023.
//

#include "Resource.h"

namespace ResourceAllocation {

    size_t Resource::nextID = 0;

    Resource::Resource() : ID(nextID++) {}

    Resource::Resource(std::string name) : name(std::move(name)), ID(nextID++) {}

    std::string Resource::GetName() const { return name; }

    size_t Resource::GetID() const { return ID; }

    bool Resource::operator<(const Resource &other) const { return ID < other.GetID(); }

}