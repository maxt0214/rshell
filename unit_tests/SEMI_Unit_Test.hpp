#ifndef _SEMI_UNIT_TEST_HPP_
#define _SEMI_UNIT_TEST_HPP_

#include "gtest/gtest.h"

#include "../header/CMD.h"
#include "../prototype/parser.h"
#include "../header/SEMI.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <vector>

//Tests for failure of both commands for semi colon
TEST(SEMIPidReturnTests, SEMI_Pid_negOneBoth_Return_Test) {
    parser userCommand("lsa ; ls-ll");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    SEMI* colon = new SEMI(Command1,Command2);
	EXPECT_EQ(colon->Execute(),-1);
}

//Tests for failure of only second command
TEST(SEMIPidReturnTests, SEMI_Pid_negOneOne_Return_Test) {
    parser userCommand("ls ; ls-ll");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    SEMI* colon = new SEMI(Command1,Command2);
    EXPECT_EQ(colon->Execute(),-1);
}

//Tests for failure of first but succcess of second
TEST(SEMIPidReturnTests, SEMI_Pid_negOneTwo_Return_Test) {
    parser userCommand("ls -ll ; ls -a");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    SEMI* colon = new SEMI(Command1,Command2);
    ASSERT_TRUE(colon->Execute() > 0);
}


//Tests to see if the commands are actually executed 
//but it would not automatically check the output of execvp(command)


TEST(SEMIExecutionTests, Test1) {
    parser userCommand("cat CMakeLists.txt ; echo I see CMakeList");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    SEMI* colon = new SEMI(Command1,Command2);
	ASSERT_TRUE(colon->Execute() > 0);
}

TEST(SEMIExecutionTests, Test2) {
    parser userCommand("echo Hello; mkdir Hello2");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    SEMI* colon = new SEMI(Command1,Command2);
    ASSERT_TRUE(colon->Execute() > 0);
}

TEST(SEMIExecutionTests, Test3) {
    parser userCommand("echo Hello; ls -l");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    SEMI* colon = new SEMI(Command1,Command2);
    ASSERT_TRUE(colon->Execute() > 0);
}

TEST(SEMIExecutionTests, Test4) {
    parser userCommand("rmdir Hello2; cat CMakeLists.txt");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    SEMI* colon = new SEMI(Command1,Command2);
    ASSERT_TRUE(colon->Execute() > 0);
}

TEST(SEMIExecutionTests, Test5) {
    parser userCommand("ls ; lsa #The first one is a command and the second one is not");
    std::vector<char**> userInput = userCommand.parse();
    Command* Command1 = new Command(userInput.at(0));
    Command* Command2 = new Command(userInput.at(2));
    SEMI* colon = new SEMI(Command1,Command2);
    EXPECT_EQ(colon->Execute(),-1);
}

#endif