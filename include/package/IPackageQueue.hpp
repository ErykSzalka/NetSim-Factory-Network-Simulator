//
// Created by eszal on 6.01.2026.
//

#ifndef NETSIM_IPACKAGEQUEUE_HPP
#define NETSIM_IPACKAGEQUEUE_HPP
#include "package/IPackageStockpile.hpp"
class IPackageQueue: public IPackageStockpile {
public:
    virtual Package pop() = 0;
    [[nodiscard]] virtual PackageQueueType get_queue_type() const = 0;
    ~IPackageQueue() override = default;

};
#endif //NETSIM_IPACKAGEQUEUE_HPP
