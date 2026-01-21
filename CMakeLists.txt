cmake_minimum_required(VERSION 3.20)
project(NetSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ================== GoogleTest ==================
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ================== MAIN PROGRAM ==================
add_executable(NetSim
        src/Package/Package.cpp
        src/Package/PackageQueue.cpp
)

target_include_directories(NetSim PRIVATE include)

# ================== TESTS ==================
add_executable(NetSim_tests
        tests/Package_tests.cpp
        src/Package/Package.cpp
        src/Package/PackageQueue.cpp
        tests/nodes_tests.cpp
        tests/factory_tests.cpp
)

target_include_directories(NetSim_tests PRIVATE include)

target_link_libraries(NetSim_tests
        gtest
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(NetSim_tests)
