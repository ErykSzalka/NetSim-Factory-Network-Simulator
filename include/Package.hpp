//
// Created by eszal on 3.01.2026.
//

#ifndef NETSIM_PACKAGE_H
#define NETSIM_PACKAGE_H
#include <set>
#include <list>
#include <cstddef>
using ElementID = unsigned int;

enum class PackageQueueType {
    FIFO, LIFO
};

class Package {
    public:
    Package();

    explicit Package(ElementID id);

    Package(Package&& other) noexcept;

    Package& operator=(Package&& other) noexcept;

    Package(const Package& other) = delete;
    Package& operator=(const Package& other) = delete;

    [[nodiscard]] ElementID get_id() const;


    ~Package();
    private:
    ElementID id_;
    static std::set<ElementID> assigned_ids;
    static std::set<ElementID> freed_ids;
    static ElementID generate_id();
};
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

class IPackageQueue: public IPackageStockpile {
public:
    virtual Package pop() = 0;
    [[nodiscard]] virtual PackageQueueType get_queue_type() const = 0;
    ~IPackageQueue() override = default;

};
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

#endif //NETSIM_PACKAGE_H