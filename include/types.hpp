//
// Created by eszal on 6.01.2026.
//

#ifndef NETSIM_TYPES_HPP
#define NETSIM_TYPES_HPP
#include <functional>
#include <random>
#include <stdexcept>



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

enum class NodeColor { UNVISITED, VISITED, VERIFIED };
extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;
#endif // NETSIM_TYPES_HPP