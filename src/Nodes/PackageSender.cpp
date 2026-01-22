//
// Created by micha on 22.01.2026.
//
#include "Nodes/PackageSender.hpp"
#include "Nodes/IPackageReceiver.hpp"


void PackageSender::push_package(Package&& p) {
    buffer_.emplace(std::move(p));
}

const std::optional<Package>& PackageSender::get_sending_buffer() const {
    return buffer_;
}

void PackageSender::send_package() {
    if (buffer_) {
        if (IPackageReceiver* receiver = receiver_preferences_.choose_receiver()) {
            receiver->receive_package(std::move(*buffer_));
            buffer_.reset();
        }
    }
}