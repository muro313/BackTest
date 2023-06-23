cmake_minimum_required(VERSION 3.5)
project(MyTests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(MyTests
        OrderBookTests.cpp
        OrderTests.cpp
        Runner.cpp
        TestProfile.cpp
        )

target_link_libraries(MyTests gtest gtest_main OrderBook BackTestLib)
set_target_properties(OrderBook PROPERTIES LINKER_LANGUAGE CXX)
