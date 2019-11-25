CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(test
    prototype/parser.cpp
    src/CNT.cpp
    src/SEMI.cpp
    src/OR.cpp
    src/AND.cpp
    src/CMD.cpp
    src/Exit.cpp
    unit_tests/Unit_Test.cpp
)

ADD_EXECUTABLE(rshell
    prototype/parser.cpp
    src/CNT.cpp
    src/SEMI.cpp
    src/OR.cpp
    src/AND.cpp
    src/CMD.cpp
    src/Exit.cpp
    src/main.cpp
)

ADD_EXECUTABLE(integration_test
    prototype/parser.cpp
    src/CNT.cpp
    src/SEMI.cpp
    src/OR.cpp
    src/AND.cpp
    src/CMD.cpp
    src/Exit.cpp
    integration_tests/integration_test.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
