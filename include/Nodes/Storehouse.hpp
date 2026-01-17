#ifndef NETSIM_STOREHOUSE_HPP
#define NETSIM_STOREHOUSE_HPP

#include <memory>
#include "IPackageReceiver.hpp"
#include "package/IPackageStockpile.hpp"

class Storehouse : public IPackageReceiver
{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = nullptr);

    void receive_package(Package &&p) override;
    [[nodiscard]] ElementID get_id() const override;

    [[nodiscard]] const_iterator begin() const override;
    [[nodiscard]] const_iterator end() const override;
    [[nodiscard]] const_iterator cbegin() const override;
    [[nodiscard]] const_iterator cend() const override;
    [[nodiscard]] ReceiverType get_receiver_type() const override;

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
};

#endif // NETSIM_STOREHOUSE_HPP