CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(prototype_test
    prototype/parser.cpp
    prototype/prototype_tests.cpp
)

ADD_EXECUTABLE(Unit_test
    prototype/parser.cpp
    Source/CMD.cpp
    Source/Exit.cpp
    Unit-Tests/Unit_Test.cpp
)

TARGET_LINK_LIBRARIES(Unit_test gtest)
TARGET_COMPILE_DEFINITIONS(Unit_test PRIVATE gtest_disable_pthreads=ON)
