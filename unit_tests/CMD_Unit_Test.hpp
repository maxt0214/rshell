#ifndef _CMD_UNIT_TEST_HPP_
#define _CMD_UNIT_TEST_HPP_

#include "gtest/gtest.h"

#include "../header/CMD.h"
#include "../prototype/parser.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include <string>
//Tests for Returning pid
TEST(CommandPidReturnTests, Pid_negOne_Return_Test) {
    parser userCommand("lsa");
    Command* singleCommand = new Command(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),-1);
}

TEST(CommandPidReturnTests, Pid_Parent_Return_Test) {
    parser userCommand("ls");
    Command* singleCommand = new Command(userCommand.parse().at(0));
	ASSERT_TRUE(singleCommand->Execute() > 0);
}

//Tests to see if the commands are actually executed 
//but it would not automatically check the output of execvp(command)
TEST(CommandExecutionTests, Command_cat_Test) {
    parser userCommand("cat CMakeLists.txt");
    Command* singleCommand = new Command(userCommand.parse().at(0));
	ASSERT_TRUE(singleCommand->Execute() > 0);
}

TEST(CommandExecutionTests, Command_pwd_Test) {
    parser userCommand("pwd");
    Command* singleCommand = new Command(userCommand.parse().at(0));
	ASSERT_TRUE(singleCommand->Execute() > 0);
}

TEST(CommandExecutionTests, Command_echo_Test) {
    parser userCommand("echo Hello");
    Command* singleCommand = new Command(userCommand.parse().at(0));
	ASSERT_TRUE(singleCommand->Execute() > 0);
}

TEST(CommandExecutionTests, Command_mkdir_Test) {
    parser userCommand("mkdir Hello");
    Command* singleCommand = new Command(userCommand.parse().at(0));
	ASSERT_TRUE(singleCommand->Execute() > 0);
}

TEST(CommandExecutionTests, Command_rmdir_Test) {
    parser userCommand("rmdir Hello");
    Command* singleCommand = new Command(userCommand.parse().at(0));
	ASSERT_TRUE(singleCommand->Execute() > 0);
}


TEST(CommandExecutionTests, Command_lslong_Test) {
    parser userCommand("ls -l");
    Command* singleCommand = new Command(userCommand.parse().at(0));
	ASSERT_TRUE(singleCommand->Execute() > 0);
}

TEST(CommandExecutionTests, Command_Comment_Test) {
    parser userCommand("ls #ls");
    Command* singleCommand = new Command(userCommand.parse().at(0));
	ASSERT_TRUE(singleCommand->Execute() > 0);
}

#endif