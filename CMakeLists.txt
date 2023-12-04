cmake_minimum_required(VERSION 3.20)

project(aoc23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(Source/abseil-cpp)

add_executable(main main.cpp)

target_link_libraries(main absl::strings)
