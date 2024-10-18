cmake_minimum_required(VERSION 3.10)
project(PokerUnitTests)


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add GoogleTest
add_subdirectory(../googletest googletest)


## Add the test executable
add_executable(PokerTests
		Card_Tests.cpp 
		Deck_Tests.cpp
		Board_Tests.cpp
		Hand_Tests.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/src/card.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/src/deck.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/src/board.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/src/hand.cpp
		)

# Link GoogleTest libraries
target_link_libraries(PokerTests gtest gtest_main)

# Include directories - Add the path to card.h
target_include_directories(PokerTests PRIVATE /Users/joshjacoby/Desktop/Code/Poker/Poker ../googletest/googletest/include)
