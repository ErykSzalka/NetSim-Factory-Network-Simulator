//
// Created by micha on 22.01.2026.
//
#include "Nodes/ReceiverPreferences.hpp"
#include "Nodes/IPackageReceiver.hpp"
#include <algorithm>

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator pg)
    : pg_(pg) {}

void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    if (!r) return;

    preferences_[r] = 1.0;

    double scale = 1.0 / preferences_.size();
    for (auto& [_, prob] : preferences_) {
        prob = scale;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    preferences_.erase(r);

    if (preferences_.empty()) return;

    double scale = 1.0 / preferences_.size();
    for (auto& [_, prob] : preferences_) {
        prob = scale;
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    if (preferences_.empty()) return nullptr;

    double p = pg_();
    double cumulative = 0.0;

    for (auto& [receiver, prob] : preferences_) {
        cumulative += prob;
        if (p < cumulative) {
            return receiver;
        }
    }

    return preferences_.rbegin()->first;
}

const ReceiverPreferences::preferences_t&
ReceiverPreferences::get_preferences() const {
    return preferences_;
}

ReceiverPreferences::const_iterator ReceiverPreferences::begin() const {
    return preferences_.begin();
}
ReceiverPreferences::const_iterator ReceiverPreferences::end() const {
    return preferences_.end();
}
ReceiverPreferences::const_iterator ReceiverPreferences::cbegin() const {
    return preferences_.cbegin();
}
ReceiverPreferences::const_iterator ReceiverPreferences::cend() const {
    return preferences_.cend();
}