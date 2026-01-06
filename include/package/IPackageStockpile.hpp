//
// Created by eszal on 6.01.2026.
//

#ifndef NETSIM_IPACKAGESTOCKPILE_HPP
#define NETSIM_IPACKAGESTOCKPILE_HPP
#include "package/Package.hpp"
#include <list>
#include <cstddef>
class IPackageStockpile {
public:

    using const_iterator = std::list<Package>::const_iterator;

    virtual void push(Package&& package) = 0;
    [[nodiscard]] virtual bool empty() const = 0;
    [[nodiscard]] virtual std::size_t size() const = 0;

    [[nodiscard]] virtual const_iterator begin() const = 0;
    [[nodiscard]] virtual const_iterator end() const = 0;

    [[nodiscard]] virtual const_iterator cbegin() const = 0;
    [[nodiscard]] virtual const_iterator cend() const = 0;
    virtual ~IPackageStockpile() = default;


};

#endif //NETSIM_IPACKAGESTOCKPILE_HPP