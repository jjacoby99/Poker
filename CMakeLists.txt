cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Poker VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

# Set the directory for nlohmann_json
set(nlohmann_json_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/vcpkg/installed/arm64-osx/share/nlohmann_json")

# Find the nlohmann_json package
find_package(nlohmann_json CONFIG REQUIRED)

# Include directories for your main source files
include_directories(${PROJECT_SOURCE_DIR}/src)

# Specify the source files in the src directory
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Specify the header files in the include directory
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)

# Add the executable
add_executable(Poker ${SOURCES})

target_link_libraries(Poker PRIVATE nlohmann_json::nlohmann_json)


# Include directories for headers
target_include_directories(Poker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
