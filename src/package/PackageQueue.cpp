//
// Created by eszal on 6.01.2026.
//
#include "Package/PackageQueue.hpp"
#include <utility>
PackageQueue::PackageQueue(PackageQueueType type) : type_(type) {}

void PackageQueue::push(Package&& package) {
    container_.push_back(std::move(package));
}

Package PackageQueue::pop() {
    Package pkg = (type_ == PackageQueueType::FIFO)
        ? std::move(container_.front())
        : std::move(container_.back());

    if (type_ == PackageQueueType::FIFO)
        container_.pop_front();
    else
        container_.pop_back();

    return pkg;
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