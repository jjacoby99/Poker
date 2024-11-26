cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Poker VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Find the SFML package and required components
#find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Include directories for your main source files
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(/Users/joshjacoby/Desktop/Code/Libraries/json-develop/include)


# Specify the source files in the src directory
file(GLOB_RECURSE SOURCES
    /Users/joshjacoby/Desktop/Code/Poker/Poker/src/*.cpp
)

# Specify the header files in the include directory
file(GLOB_RECURSE HEADERS
    /Users/joshjacoby/Desktop/Code/Poker/Poker/include/*.h
)

# Add the executable
add_executable(Poker ${SOURCES} ${HEADERS})

# Include directories for headers
target_include_directories(Poker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Optional: If you're using Google Test for unit testing
# Uncomment the following lines if you decide to implement unit tests
# find_package(GTest REQUIRED)
# target_link_libraries(Poker GTest::GTest GTest::Main)
