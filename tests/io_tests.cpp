//
// Created by eszal on 24.01.2026.
//
#include <gtest/gtest.h>

#include "IO/io_fun.hpp"
TEST(FactoryIOTest, ParseRamp) {
    std::istringstream iss("LOADING_RAMP id=1 delivery-interval=3");
    auto factory = load_factory_structure(iss);

    ASSERT_EQ(std::next(factory.ramp_cbegin(), 1), factory.ramp_cend());
    const auto& r = *(factory.ramp_cbegin());
    EXPECT_EQ(1, r.get_id());
    EXPECT_EQ(3, r.get_delivery_interval());
}