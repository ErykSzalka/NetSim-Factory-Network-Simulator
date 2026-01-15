#ifndef NETSIM_RAMP_HPP
#define NETSIM_RAMP_HPP

#include "PackageSender.hpp"
#include "types.hpp"

class Ramp : public PackageSender
{
public:
    Ramp(ElementID id, TimeOffset di);

    void deliver_goods(Time t);

    [[nodiscard]] TimeOffset get_delivery_interval() const;
    [[nodiscard]] ElementID get_id() const;

private:
    ElementID id_;
    TimeOffset di_;
};

#endif // NETSIM_RAMP_HPP