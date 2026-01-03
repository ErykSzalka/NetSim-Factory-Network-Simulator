cmake_minimum_required(VERSION 4.1)
project(NetSim)

set(CMAKE_CXX_STANDARD 20)

add_executable(NetSim main.cpp
        include/package.h)
