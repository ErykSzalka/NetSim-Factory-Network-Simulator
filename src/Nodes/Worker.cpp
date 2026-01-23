//
// Created by micha on 22.01.2026.
//
#include "Nodes/Worker.hpp"

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q)
    : id_(id), pd_(pd), q_(std::move(q)) {}

void Worker::do_work(Time t) {
    if (!processed_package_ && !q_->empty()) {
        processed_package_.emplace(q_->pop());
        processing_start_time_ = t;
    }

    if (processed_package_) {
        if (t - processing_start_time_ + 1 == pd_) {
            push_package(std::move(*processed_package_));
            processed_package_.reset();
        }
    }
}
IPackageQueue* Worker::get_queue() const {
    return q_.get();
}
void Worker::receive_package(Package&& p) {
    q_->push(std::move(p));
}

TimeOffset Worker::get_processing_duration() const { return pd_; }
Time Worker::get_package_processing_start_time() const { return processing_start_time_; }
ElementID Worker::get_id() const { return id_; }

Worker::const_iterator Worker::begin() const { return q_->begin(); }
Worker::const_iterator Worker::end() const { return q_->end(); }
Worker::const_iterator Worker::cbegin() const { return q_->cbegin(); }
Worker::const_iterator Worker::cend() const { return q_->cend(); }

ReceiverType Worker::get_receiver_type() const { return ReceiverType::WORKER; }