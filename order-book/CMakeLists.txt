cmake_minimum_required(VERSION 3.10)
project(orderbook CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Download and add GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(order-book main.cpp)

# Add a basic test
add_executable(basic_test tests/test_basic.cpp)
target_link_libraries(basic_test gtest_main)
add_test(NAME BasicTest COMMAND basic_test)
