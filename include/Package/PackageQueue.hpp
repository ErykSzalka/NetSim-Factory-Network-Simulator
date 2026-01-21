//
// Created by eszal on 6.01.2026.
//

#ifndef NETSIM_PACKAGEQUEUE_HPP
#define NETSIM_PACKAGEQUEUE_HPP
#include <list>

#include "Package/IPackageQueue.hpp"
class PackageQueue: public IPackageQueue {
public:
    explicit PackageQueue(PackageQueueType type);
    void push(Package&& package) override;
    Package pop() override;

    [[nodiscard]] bool empty() const override;
    [[nodiscard]] std::size_t size() const override;

    [[nodiscard]] const_iterator begin() const override;
    [[nodiscard]] const_iterator end() const override;
    [[nodiscard]] const_iterator cbegin() const override;
    [[nodiscard]] const_iterator cend() const override;
    [[nodiscard]] PackageQueueType get_queue_type() const override;
private:
    PackageQueueType type_;
    std::list<Package> container_;

};
#endif //NETSIM_PACKAGEQUEUE_HPP