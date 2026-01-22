//
// Created by micha on 22.01.2026.
//
#include "Nodes/Ramp.hpp"
#include "package/Package.hpp"

Ramp::Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}

void Ramp::deliver_goods(Time t) {
    if ((t - 1) % di_ == 0) {
        push_package(Package());
    }
}

TimeOffset Ramp::get_delivery_interval() const { return di_; }
ElementID Ramp::get_id() const { return id_; }