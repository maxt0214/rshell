#include "CMD_Unit_Test.hpp"
#include "Exit_Unit_Test.hpp"
#include "AND_Unit_Test.hpp"
#include "OR_Unit_Test.hpp"
#include "SEMI_Unit_Test.hpp"

#include "gtest/gtest.h"

//main for tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}