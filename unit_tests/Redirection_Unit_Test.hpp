#ifndef _REDIRECTION_UNIT_TEST_HPP_
#define _REDIRECTION_UNIT_TEST_HPP_

#include "gtest/gtest.h"

#include "../header/CMD.h"
#include "../prototype/parser.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h> 
#include <fstream>
#include <vector>

TEST(RedirectionExecutionTests, Redirection_Success1) {
    parser userCommand("cat < CMakeLists.txt");
    std::vector<char**> userInput = userCommand.parse();
    Command* curr = new Command(userInput.at(0));
    
    char* fileName = userInput.at(2)[0];
    int fds = open(fileName, O_RDONLY);
    curr->fdModifier(fds,-1);
    
	ASSERT_TRUE(curr->Execute() > 0);
}

TEST(RedirectionExecutionTests, Redirection_Success2) {
    parser userCommand("ls > out.txt");
    std::vector<char**> userInput = userCommand.parse();
    Command* curr = new Command(userInput.at(0));
    
    char* fileName = userInput.at(2)[0];
    
    std::string filename = fileName;
    std::ofstream newFile;
    newFile.open(fileName,std::ofstream::out | std::ofstream::trunc);
    newFile.close();
    
    int fds = open(fileName, O_WRONLY | O_APPEND);
    curr->fdModifier(-1,fds);
    
	ASSERT_TRUE(curr->Execute() > 0);
}

TEST(RedirectionExecutionTests, Redirection_Success3) {
    parser userCommand("cat < CMakeLists.txt > out.txt");
    std::vector<char**> userInput = userCommand.parse();
    Command* curr = new Command(userInput.at(0));
    
    char* fileName = userInput.at(2)[0];
    
    int fds = open(fileName, O_RDONLY);
    curr->fdModifier(fds,-1);
    
    fileName = userInput.at(4)[0];
    std::string filename = fileName;
    std::ofstream newFile;
    newFile.open(fileName,std::ofstream::out | std::ofstream::trunc);
    newFile.close();
    
    fds = open(fileName, O_WRONLY | O_APPEND);
    curr->fdModifier(-1,fds);
    
	ASSERT_TRUE(curr->Execute() > 0);
}

#endif

