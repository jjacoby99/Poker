cmake_minimum_required(VERSION 3.10)
project(CardTests)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add GoogleTest
add_subdirectory(../googletest googletest)

# Add the test executable
add_executable(CardTests 
		Card_Tests.cpp 
		Deck_Tests.cpp
		Board_Tests.cpp
		Hand_Tests.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/card.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/deck.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/board.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/hand.cpp
		)

# Link GoogleTest libraries
target_link_libraries(CardTests gtest gtest_main)

# Include directories - Add the path to card.h
target_include_directories(CardTests PRIVATE /Users/joshjacoby/Desktop/Code/Poker/Poker ../googletest/googletest/include)
