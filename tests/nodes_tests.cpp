//
// Created by eszal on 21.01.2026.
//
#pragma once
#include <gtest/gtest.h>

#include "Nodes/Worker.hpp"
#include "Package/PackageQueue.hpp"
TEST(WorkerTest, HasBuffer) {

    Worker w(1, 2, std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Time t = 1;

    w.receive_package(Package(1));
    w.do_work(t);
    ++t;
    w.receive_package(Package(2));
    w.do_work(t);
    auto& buffer = w.get_sending_buffer();

    ASSERT_TRUE(buffer.has_value());
    EXPECT_EQ(buffer.value().get_id(), 1);
}

