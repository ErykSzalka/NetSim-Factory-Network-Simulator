#ifndef NETSIM_WORKER_HPP
#define NETSIM_WORKER_HPP

#include <memory>
#include <optional>

#include "PackageSender.hpp"
#include "IPackageReceiver.hpp"
#include "Package/IPackageQueue.hpp"

class Worker : public PackageSender, public IPackageReceiver
{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q);

    void do_work(Time t);

    [[nodiscard]] TimeOffset get_processing_duration() const;
    [[nodiscard]] Time get_package_processing_start_time() const;

    void receive_package(Package &&p) override;
    [[nodiscard]] ElementID get_id() const override;

    [[nodiscard]] const_iterator begin() const override;
    [[nodiscard]] const_iterator end() const override;
    [[nodiscard]] const_iterator cbegin() const override;
    [[nodiscard]] const_iterator cend() const override;
    [[nodiscard]] ReceiverType get_receiver_type() const override;

private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
    Time processing_start_time_ = 0;
    std::optional<Package> processed_package_ = std::nullopt;
};

#endif // NETSIM_WORKER_HPP