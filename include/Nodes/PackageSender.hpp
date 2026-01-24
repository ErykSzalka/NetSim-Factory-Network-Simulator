#ifndef NETSIM_PACKAGESENDER_HPP
#define NETSIM_PACKAGESENDER_HPP

#include <optional>
#include "Package/package.hpp"
#include "ReceiverPreferences.hpp"

class PackageSender {
public:
    ReceiverPreferences receiver_preferences_;

    PackageSender() = default;
    PackageSender(PackageSender&&) = default;

    void push_package(Package&& p);
    void send_package();

    std::optional<Package>& get_sending_buffer();

protected:
    std::optional<Package> sending_buffer_;
};

#endif // NETSIM_PACKAGESENDER_HPP