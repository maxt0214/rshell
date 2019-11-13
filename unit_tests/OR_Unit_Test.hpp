#ifndef _OR_UNIT_TEST_HPP_
#define _OR_UNIT_TEST_HPP_

#include "gtest/gtest.h"

#include "../header/CMD.h"
#include "../prototype/parser.h"
#include "../header/OR.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include <string>
//Tests for Returning pid
TEST(ORPidReturnTests, OR_Pid_negOne_Return_Test) {
    parser userCommand("lsa || lsa");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    OR* Or = new OR(Command1,Command2);
	EXPECT_EQ(Or->Execute(),-1);
}

TEST(ORPidReturnTests, OR_Pid_normal_Return_Test) {
    parser userCommand("ls || lsa");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    OR* Or = new OR(Command1,Command2);
	ASSERT_TRUE(Or->Execute() > 0);
}

TEST(ORPidReturnTests, OR_Pid_Normal_Return_Test) {
    parser userCommand("lsa || ls");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    OR* Or = new OR(Command1,Command2);
	ASSERT_TRUE(Or->Execute() > 0);
}

//Tests to see if the commands are actually executed 
//but it would not automatically check the output of execvp(command)
TEST(ORExecutionTests, OR_catORls_Test) {
    parser userCommand("cat CMakeLists.txt || ls");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    OR* Or = new OR(Command1,Command2);
	ASSERT_TRUE(Or->Execute() > 0);
}

TEST(ORExecutionTests, OR_echo_Test) {
    parser userCommand("lsa || echo Hello");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    OR* Or = new OR(Command1,Command2);
	ASSERT_TRUE(Or->Execute() > 0);
}

TEST(ORExecutionTests, OR_pwd_Test) {
    parser userCommand("sas sj || pwd");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    OR* Or = new OR(Command1,Command2);
	ASSERT_TRUE(Or->Execute() > 0);
}

TEST(ORExecutionTests, OR_comments_Test) {
    parser userCommand("lsa || ls#ssh");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    OR* Or = new OR(Command1,Command2);
	ASSERT_TRUE(Or->Execute() > 0);
}

#endif