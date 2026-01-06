cmake_minimum_required(VERSION 4.1)
project(NetSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# pliki źródłowe
add_executable(NetSim
        src/Package.cpp
)

# katalog z nagłówkami
target_include_directories(NetSim PRIVATE include)