//
// Created by eszal on 6.01.2026.
//
#include "package/Package.hpp"
#include <stdexcept>
std::set<ElementID> Package::assigned_ids;
std::set<ElementID> Package::freed_ids;

ElementID Package::generate_id() {
    if (!freed_ids.empty()) {
        const auto it = freed_ids.begin();
        const ElementID id = *it;
        freed_ids.erase(it);
        assigned_ids.insert(id);
        return id;
    }
    const ElementID new_id=assigned_ids.empty()? 1 : (*assigned_ids.rbegin()+1);
    assigned_ids.insert(new_id);
    return new_id;
}

Package::Package():id_(generate_id()){}

Package::Package(const ElementID id): id_(id){assigned_ids.insert(id);}

Package::Package(Package &&other) noexcept:id_(other.get_id()) {
    other.id_=0;
}
Package& Package::operator=(Package &&other) noexcept {
    if (this != &other) {
        id_=other.id_;
        other.id_=0;
    }
    return *this;
}
ElementID Package::get_id() const {
    return id_;
}

Package::~Package() {
    if (id_!=0) {
        assigned_ids.erase(id_);
        freed_ids.insert(id_);
    }
}

/////////////////////////////////////////////////

