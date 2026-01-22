//
// Created by micha on 22.01.2026.
//
#include "Nodes/ReceiverPreferences.hpp"
#include "Nodes/IPackageReceiver.hpp"
#include <algorithm>

using ReceiverPair = std::pair<IPackageReceiver* const, double>;

void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    auto num_of_receivers = preferences_.size();
    if (num_of_receivers == 0) {
        preferences_[r] = 1.0;
    } else {
        auto new_prob = 1.0 / static_cast<double>(num_of_receivers + 1);
        for (auto& item : preferences_) {
            item.second = new_prob;
        }
        preferences_[r] = new_prob;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    auto it = preferences_.find(r);
    if (it == preferences_.end()) return;

    preferences_.erase(it);

    auto num_of_receivers = preferences_.size();
    if (num_of_receivers == 0) return;

    auto new_prob = 1.0 / static_cast<double>(num_of_receivers);
    for (auto& item : preferences_) {
        item.second = new_prob;
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() const {
    double prob = pg_();

    if (prob >= 0 && prob <= 1) {
        double distribution = 0.0;
        for (const auto& item : preferences_) {
            distribution += item.second;
            if (prob <= distribution) {
                return item.first;
            }
        }
        if (!preferences_.empty()) {
            return preferences_.rbegin()->first;
        }
    }
    return nullptr;
}

const ReceiverPreferences::preferences_t& ReceiverPreferences::get_preferences() const {
    return preferences_;
}

ReceiverPreferences::const_iterator ReceiverPreferences::begin() const { return preferences_.begin(); }
ReceiverPreferences::const_iterator ReceiverPreferences::end() const { return preferences_.end(); }
ReceiverPreferences::const_iterator ReceiverPreferences::cbegin() const { return preferences_.cbegin(); }
ReceiverPreferences::const_iterator ReceiverPreferences::cend() const { return preferences_.cend(); }