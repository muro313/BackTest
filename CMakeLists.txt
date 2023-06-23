cmake_minimum_required(VERSION 3.5)
project(BackTest)

set(CMAKE_CXX_STANDARD 20)

include_directories(OrderBook)
include_directories(lib)
add_subdirectory(OrderBook)
add_subdirectory(tests)
add_subdirectory(lib)
add_subdirectory(Time)
include_directories(Time)
