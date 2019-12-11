#ifndef _TEST_UNIT_TEST_HPP_
#define _TEST_UNIT_TEST_HPP_

#include "gtest/gtest.h"

#include "../header/Test.h"
#include "../prototype/parser.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include <string>

TEST(TestExecutionTests, testEFlag_Fail1) {
    parser userCommand("-e test/file/path");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),-1);
}

TEST(TestExecutionTests, testDFlag_Fail1) {
    parser userCommand("-d test/file/path");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),-1);
}

TEST(TestExecutionTests, testFFlag_Fail1) {
    parser userCommand("-f test/file/path");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),-1);
}


TEST(TestExecutionTests, testEFlag_Fail2) {
    parser userCommand("-e lssakdfjaljfiewj");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),-1);
}

TEST(TestExecutionTests, testDFlag_Fail2) {
    parser userCommand("-d lssakdfjaljfiewj");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),-1);
}

TEST(TestExecutionTests, testFFlag_Fail2) {
    parser userCommand("-f lssakdfjaljfiewj");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),-1);
}

TEST(TestExecutionTests, testNOFlag_Fail2) {
    parser userCommand("ssakdfjaljfiewj");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),-1);
}

TEST(TestExecutionTests, testEFlag_Success1) {
    parser userCommand("-e src/Test.cpp");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),0);
}

TEST(TestExecutionTests, testfFlag_Success1) {
    parser userCommand("-f src/Test.cpp");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),0);
}

TEST(TestExecutionTests, testDFlag_Success1) {
    parser userCommand("-d src");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),0);
}

TEST(TestExecutionTests, testNOFlag_Success1) {
    parser userCommand("src/Test.cpp");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),0);
}

TEST(TestExecutionTests, testEFlag_Success2) {
    parser userCommand("-e header/Test.h");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),0);
}

TEST(TestExecutionTests, testFFlag_Success2) {
    parser userCommand("-f header/Test.h");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),0);
}

TEST(TestExecutionTests, testDFlag_Success2) {
    parser userCommand("-d header");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),0);
}

TEST(TestExecutionTests, testNOFlag_Success2) {
    parser userCommand("header/Test.h");
    TestCmd* singleCommand = new TestCmd(userCommand.parse().at(0));
	EXPECT_EQ(singleCommand->Execute(),0);
}

#endif

