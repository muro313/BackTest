project(OrderBook)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES OrderBook.cpp Order.cpp)
set(HEADER_FILES OrderBook.h Order.h)

add_executable(OrderBookRun ${SOURCE_FILES} ${HEADER_FILES})
add_library(OrderBook STATIC ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(OrderBook PROPERTIES LINKER_LANGUAGE CXX)