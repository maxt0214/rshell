CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(prototype_test
    prototype/parser.cpp
    prototype/prototype_tests.cpp
)

ADD_EXECUTABLE(Command_unit_test
    prototype/parser.cpp
    Source/CMD.cpp
    Unit-Tests/CMD_Unit_Test.cpp
)

TARGET_LINK_LIBRARIES(Command_unit_test gtest)
TARGET_COMPILE_DEFINITIONS(Command_unit_test PRIVATE gtest_disable_pthreads=ON)
