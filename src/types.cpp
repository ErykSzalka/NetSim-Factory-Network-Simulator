//
// Created by eszal on 24.01.2026.
//
#include "types.hpp"

#include <cstdlib>
#include <random>


std::random_device rd;
std::mt19937 rng(rd());

double default_probability_generator() {
    return std::generate_canonical<double, 10>(rng);
}

std::function<double()> probability_generator = default_probability_generator;
