//
// Created by eszal on 6.01.2026.
//
#include "Package.hpp"
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
        id_=other.get_id();
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

PackageQueue::PackageQueue(PackageQueueType type): type_(type){}

void PackageQueue::push(Package&& package) {
    container_.push_back(std::move(package));
}

Package PackageQueue::pop() {
    if (container_.empty()) {
        throw std::logic_error("Package queue is empty");
    }
    Package result=std::move(type_==PackageQueueType::FIFO?container_.front():container_.back());
    if (type_==PackageQueueType::FIFO) {
        container_.pop_front();
    }else {
        container_.pop_back();
    }
    return result;
}
bool PackageQueue::empty() const {
    return container_.empty();
}
std::size_t PackageQueue::size() const {
    return container_.size();
}
PackageQueue::const_iterator PackageQueue::begin() const {
    return container_.begin();

}
PackageQueue::const_iterator PackageQueue::end() const {
    return container_.end();
}

PackageQueue::const_iterator PackageQueue::cbegin() const {
    return container_.cbegin();

}
PackageQueue::const_iterator PackageQueue::cend() const {
    return container_.cend();
}

PackageQueueType PackageQueue::get_queue_type() const {
    return type_;
}
