project(OrderBook)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES Time.cpp)
set(HEADER_FILES Time.h)

add_executable(TimeRun ${SOURCE_FILES} ${HEADER_FILES})
add_library(Time STATIC ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(Time PROPERTIES LINKER_LANGUAGE CXX)