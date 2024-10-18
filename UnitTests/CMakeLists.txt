# Specify the CMake minimum version and project name
cmake_minimum_required(VERSION 3.10)
project(PokerUnitTests)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Find the Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add your test source files
set(TEST_SOURCES
    Board_Tests.cpp
    Deck_Tests.cpp
    Hand_Tests.cpp
    Card_Tests.cpp
    Player_Tests.cpp
    Sim_Tests.cpp
)

# Create the test executable
add_executable(PokerTests ${TEST_SOURCES})

# Link the Google Test libraries
target_link_libraries(PokerTests ${GTEST_LIBRARIES} pthread)

# If you have additional include directories
include_directories(../include ../src)
