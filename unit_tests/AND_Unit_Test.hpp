#ifndef _AND_UNIT_TEST_HPP_
#define _AND_UNIT_TEST_HPP_

#include "gtest/gtest.h"

#include "../header/CMD.h"
#include "../prototype/parser.h"
#include "../header/AND.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <vector>

#include <string>
//Tests for Returning pid
TEST(ANDPidReturnTests, AND_Pid_negOne_Return_Test) {
    parser userCommand("lsa && ls");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    AND* And = new AND(Command1,Command2);
	EXPECT_EQ(And->Execute(),-1);
}

TEST(ANDPidReturnTests, AND_Pid_NegOne_Return_Test) {
    parser userCommand("ls && lsa");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    AND* And = new AND(Command1,Command2);
	EXPECT_EQ(And->Execute(),-1);
}

TEST(ANDPidReturnTests, AND_Pid_Parent_Return_Test) {
    parser userCommand("ls && ls");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    AND* And = new AND(Command1,Command2);
	ASSERT_TRUE(And->Execute() > 0);
}

//Tests to see if the commands are actually executed 
//but it would not automatically check the output of execvp(command)
TEST(ANDExecutionTests, AND_catAndls_Test) {
    parser userCommand("cat CMakeLists.txt && ls");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    AND* And = new AND(Command1,Command2);
	ASSERT_TRUE(And->Execute() > 0);
}

TEST(ANDExecutionTests, AND_pwdAndls_Test) {
    parser userCommand("pwd && ls");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    AND* And = new AND(Command1,Command2);
	ASSERT_TRUE(And->Execute() > 0);
}

TEST(ANDExecutionTests, AND_echoAndecho_Test) {
    parser userCommand("echo Hello && echo Man");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    AND* And = new AND(Command1,Command2);
	ASSERT_TRUE(And->Execute() > 0);
}

TEST(ANDExecutionTests, AND_mkdirAndrmdir_Test) {
    parser userCommand("mkdir Bye && rmdir Bye");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    AND* And = new AND(Command1,Command2);
	ASSERT_TRUE(And->Execute() > 0);
}

TEST(ANDExecutionTests, AND_lslongAndlsa_Test) {
    parser userCommand("ls -l && ls -a");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    AND* And = new AND(Command1,Command2);
	ASSERT_TRUE(And->Execute() > 0);
}

TEST(ANDExecutionTests, AND_Comment_Test) {
    parser userCommand("ls && pwd #ls && rm");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    AND* And = new AND(Command1,Command2);
	ASSERT_TRUE(And->Execute() > 0);
}

#endif