cmake_minimum_required(VERSION 3.10)
project(PokerUnitTests)


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "/Users/joshjacoby/Desktop/Code/Poker/Poker/external/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")


# Add GoogleTest
add_subdirectory(../googletest googletest)

# Set the directory for nlohmann_json
set(nlohmann_json_DIR "/Users/joshjacoby/Desktop/Code/Poker/Poker/external/vcpkg/installed/arm64-osx/share/nlohmann_json")

# Find the nlohmann_json package
find_package(nlohmann_json CONFIG REQUIRED)


# Include directories for your main source files
include_directories(/Users/joshjacoby/Desktop/Code/Poker/Poker/src)

# Specify the source files in the src directory
file(GLOB_RECURSE SOURCES /Users/joshjacoby/Desktop/Code/Poker/Poker/src/*.cpp)

# Specify the header files in the include directory
file(GLOB_RECURSE HEADERS /Users/joshjacoby/Desktop/Code/Poker/Poker/include/*.h)

## Add the test executable
add_executable(PokerTests
		Card_Tests.cpp 
		Deck_Tests.cpp
		Board_Tests.cpp
		Hand_Tests.cpp
		Range_Tests.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/src/card.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/src/deck.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/src/board.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/src/hand.cpp
		/Users/joshjacoby/Desktop/Code/Poker/Poker/src/range.cpp
		)


		
# Link GoogleTest libraries
target_link_libraries(PokerTests gtest gtest_main)

target_link_libraries(PokerTests nlohmann_json::nlohmann_json)

# Include directories - Add the path to card.h
target_include_directories(PokerTests PRIVATE
    /Users/joshjacoby/Desktop/Code/Poker/Poker/src
    /Users/joshjacoby/Desktop/Code/Poker/Poker/include  
    ../googletest/googletest/include
)

# Include directories for headers
target_include_directories(PokerTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
