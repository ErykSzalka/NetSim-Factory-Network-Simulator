//
// Created by micha on 22.01.2026.
//
#include "Nodes/PackageSender.hpp"
#include "Nodes/IPackageReceiver.hpp"


void PackageSender::push_package(Package&& p) {
    sending_buffer_.emplace(std::move(p));
}

std::optional<Package>& PackageSender::get_sending_buffer() {
    return sending_buffer_;
}

void PackageSender::send_package() {
    if (sending_buffer_) {
        if (IPackageReceiver* receiver = receiver_preferences_.choose_receiver()) {
            receiver->receive_package(std::move(*sending_buffer_));
            sending_buffer_.reset();
        }
    }
}