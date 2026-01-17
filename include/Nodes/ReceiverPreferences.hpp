#ifndef NETSIM_RECEIVERPREFERENCES_HPP
#define NETSIM_RECEIVERPREFERENCES_HPP

#include <map>
#include "types.hpp"

class IPackageReceiver;

class ReceiverPreferences
{
public:
    using preferences_t = std::map<IPackageReceiver *, double>;
    using const_iterator = preferences_t::const_iterator;

    explicit ReceiverPreferences(ProbabilityGenerator pg = [](double d = 1.0)
                                 { return 0.0; });

    void add_receiver(IPackageReceiver *r);
    void remove_receiver(IPackageReceiver *r);

    [[nodiscard]] IPackageReceiver *choose_receiver();
    [[nodiscard]] const preferences_t &get_preferences() const;

    [[nodiscard]] const_iterator begin() const;
    [[nodiscard]] const_iterator end() const;
    [[nodiscard]] const_iterator cbegin() const;
    [[nodiscard]] const_iterator cend() const;

private:
    preferences_t preferences_;
    ProbabilityGenerator pg_;
};

#endif // NETSIM_RECEIVERPREFERENCES_HPP