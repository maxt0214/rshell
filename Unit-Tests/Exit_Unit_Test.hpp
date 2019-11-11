#ifndef _EXIT_UNIT_TEST_HPP_
#define _EXIT_UNIT_TEST_HPP_

#include "gtest/gtest.h"

#include "/home/ec2-user/environment/assignment-a1w_alums/Headers/Exit.h"
#include "/home/ec2-user/environment/assignment-a1w_alums/prototype/parser.h"

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
    parser userCommand("pwd");
    Exit* singleCommand = new Exit(userCommand.parse().at(0));
	ASSERT_TRUE(singleCommand->Execute() > 0);
}

#endif