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
        src/package/Package.cpp
        src/package/PackageQueue.cpp
)

target_include_directories(NetSim PRIVATE include)

# ================== TESTS ==================
add_executable(NetSim_tests
        tests/package_tests.cpp
        src/package/Package.cpp
        src/package/PackageQueue.cpp
)

target_include_directories(NetSim_tests PRIVATE include)

target_link_libraries(NetSim_tests
        gtest
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(NetSim_tests)
