//
// Created by micha on 22.01.2026.
//
#include "Nodes/Storehouse.hpp"

Storehouse::Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d)
    : id_(id), d_(std::move(d)) {}

void Storehouse::receive_package(Package&& p) {
    d_->push(std::move(p));
}

ElementID Storehouse::get_id() const { return id_; }

Storehouse::const_iterator Storehouse::begin() const { return d_->begin(); }
Storehouse::const_iterator Storehouse::end() const { return d_->end(); }
Storehouse::const_iterator Storehouse::cbegin() const { return d_->cbegin(); }
Storehouse::const_iterator Storehouse::cend() const { return d_->cend(); }

ReceiverType Storehouse::get_receiver_type() const { return ReceiverType::STOREHOUSE; }