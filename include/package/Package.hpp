//
// Created by eszal on 3.01.2026.
//

#ifndef NETSIM_PACKAGE_HPP
#define NETSIM_PACKAGE_HPP
#include <set>

#include "package/types.hpp"

class Package {
    public:
    Package();

    explicit Package(ElementID id);

    Package(Package&& other) noexcept;

    Package& operator=(Package&& other) noexcept;

    Package(const Package& other) = delete;
    Package& operator=(const Package& other) = delete;

    [[nodiscard]]ElementID get_id() const;


    ~Package();
    private:
    ElementID id_;
    static std::set<ElementID> assigned_ids;
    static std::set<ElementID> freed_ids;
    static ElementID generate_id();
};
#endif //NETSIM_PACKAGE_HPP