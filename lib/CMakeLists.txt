project(BackTestLib)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES
        BackTest.cpp
        Exchange.cpp
        History.cpp
        Model.cpp
        Data.cpp
        Robot.cpp
        Portfolio.cpp)

set(HEADER_FILES
        BackTest.h
        Exchange.h
        History.h
        Model.h
        Data.h
        Robot.h
        Portfolio.h)

add_executable(BackTestLibRun ${SOURCE_FILES} ${HEADER_FILES})
add_library(BackTestLib STATIC ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(BackTestLib PROPERTIES LINKER_LANGUAGE CXX)