#ifndef NETSIM_PACKAGESENDER_HPP
#define NETSIM_PACKAGESENDER_HPP

#include <optional>
#include "package.hpp"
#include "ReceiverPreferences.hpp"

class PackageSender
{
public:
    PackageSender() = default;
    PackageSender(PackageSender &&) = default;
    virtual ~PackageSender() = default;

    void send_package();

    [[nodiscard]] const std::optional<Package> &get_sending_buffer() const;

    void push_package(Package &&p);

    ReceiverPreferences receiver_preferences_;

protected:
    std::optional<Package> buffer_ = std::nullopt;
};

#endif // NETSIM_PACKAGESENDER_HPP