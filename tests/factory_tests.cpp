//
// Created by eszal on 21.01.2026.
//
#pragma once
#include <gtest/gtest.h>

#include "Factory/Factory.hpp"
#include "Nodes/Ramp.hpp"
#include "Nodes/Storehouse.hpp"
#include "Nodes/Worker.hpp"
#include "Package/PackageQueue.hpp"

TEST(FactoryTest, IsConsistentCorrect) {

    Factory factory;
    factory.add_ramp(Ramp(1, 1));
    factory.add_worker(Worker(1, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));
    factory.add_storehouse(Storehouse(1));

    Ramp& r = *(factory.find_ramp_by_id(1));
    r.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(1)));

    Worker& w = *(factory.find_worker_by_id(1));
    w.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(1)));

    EXPECT_TRUE(factory.is_consistent());
}



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

