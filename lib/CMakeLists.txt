project(BackTestLib)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES
        BackTest.cpp
        History.cpp
        Model.cpp
        Data.cpp
        Portfolio.cpp)

set(HEADER_FILES
        BackTest.h
        History.h
        Model.h
        Data.h
        Portfolio.h)

add_executable(BackTestLibRun ${SOURCE_FILES} ${HEADER_FILES})
add_library(BackTestLib STATIC ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(BackTestLib PROPERTIES LINKER_LANGUAGE CXX)