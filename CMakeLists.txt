cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Poker VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Include directories for your main source files
include_directories(${PROJECT_SOURCE_DIR}/src)

include_directories(/Users/joshjacoby/Desktop/Code/Libraries/json-develop/include)


# Specify the source files in the src directory
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Specify the header files in the include directory
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)

# Add the executable
add_executable(Poker ${SOURCES} ${HEADERS})

# Include directories for headers
target_include_directories(Poker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


