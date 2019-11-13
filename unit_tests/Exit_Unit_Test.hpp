#ifndef _EXIT_UNIT_TEST_HPP_
#define _EXIT_UNIT_TEST_HPP_

#include "gtest/gtest.h"

#include "../header/Exit.h"
#include "../prototype/parser.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include <string>

//Test to see if the program is exitted correctly
TEST(ExitExecutionTests, Exit_Exit_Test) {
    parser userCommand("exit");
    Exit* singleCommand = new Exit(userCommand.parse().at(0));
	ASSERT_EXIT(singleCommand->Execute(),::testing::ExitedWithCode(0),"");
}

TEST(ExitExecutionTests, Exit_Not_Exit_Test) {
    parser userCommand("echo hello");
    Exit* singleCommand = new Exit(userCommand.parse().at(0));
	ASSERT_TRUE(singleCommand->Execute() > 0);
}

#endif