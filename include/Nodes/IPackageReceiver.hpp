#ifndef NETSIM_IPACKAGERECEIVER_HPP
#define NETSIM_IPACKAGERECEIVER_HPP

#include "types.hpp"
#include "Package/Package.hpp"
#include "Package/IPackageStockpile.hpp"

class IPackageReceiver
{
public:
    using const_iterator = IPackageStockpile::const_iterator;

    virtual ~IPackageReceiver() = default;

    virtual void receive_package(Package &&p) = 0;

    [[nodiscard]] virtual ElementID get_id() const = 0;

    [[nodiscard]] virtual const_iterator begin() const = 0;
    [[nodiscard]] virtual const_iterator end() const = 0;
    [[nodiscard]] virtual const_iterator cbegin() const = 0;
    [[nodiscard]] virtual const_iterator cend() const = 0;
    [[nodiscard]] virtual ReceiverType get_receiver_type() const = 0;
};

#endif // NETSIM_IPACKAGERECEIVER_HPP