cmake_minimum_required(VERSION 3.10)
project(hashmap C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add Unity test framework
include(FetchContent)
FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.5.2
)
FetchContent_MakeAvailable(unity)

# Main executable
add_executable(hashmap hashmap.c)

# Test executable
add_executable(hashmap_tests tests.c)
target_link_libraries(hashmap_tests PRIVATE unity)

# Enable testing
enable_testing()
add_test(NAME hashmap_tests COMMAND hashmap_tests)

# Set compiler warnings
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(hashmap PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(hashmap_tests PRIVATE -Wall -Wextra -Wpedantic)
endif() 