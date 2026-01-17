//
// Created by eszal on 6.01.2026.
//

#ifndef NETSIM_TYPES_HPP
#define NETSIM_TYPES_HPP
#include <functional>

using ElementID = unsigned int;

enum class PackageQueueType
{
    FIFO,
    LIFO
};

enum class ReceiverType
{
    WORKER,
    STOREHOUSE
};

using Time = int;

using TimeOffset = int;

using ProbabilityGenerator = std::function<double()>;

#endif // NETSIM_TYPES_HPP