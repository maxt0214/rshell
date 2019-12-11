#ifndef _PIPE_UNIT_TEST_HPP_
#define _PIPE_UNIT_TEST_HPP_

#include "gtest/gtest.h"

#include "../header/CMD.h"
#include "../header/pipe.h"
#include "../prototype/parser.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h> 
#include <fstream>
#include <vector>

TEST(PipeExecutionTests, Pipe_Success1) {
    parser userCommand("cat < CMakeLists.txt | sort");
    std::vector<char**> userInput = userCommand.parse();
    Base* curr = new Command(userInput.at(0));
    
    char* fileName = userInput.at(2)[0];
    int fds = open(fileName, O_RDONLY);
    curr->fdModifier(fds,-1);
    
    curr = new Pipe(curr,new Command(userInput.at(4)));
    
	ASSERT_TRUE(curr->Execute() > 0);
}

TEST(PipeExecutionTests, Pipe_Success2) {
    parser userCommand("cat < CMakeLists.txt | sort > out.txt");
    std::vector<char**> userInput = userCommand.parse();
    Base* curr = new Command(userInput.at(0)), * rt = new Command(userInput.at(4));
    
    char* fileName = userInput.at(2)[0];
    int fds = open(fileName, O_RDONLY);
    curr->fdModifier(fds,-1);
    
    fileName = userInput.at(6)[0];
    std::string filename = fileName;
    std::ofstream newFile;
    newFile.open(fileName,std::ofstream::out | std::ofstream::trunc);
    newFile.close();
    
    fds = open(fileName, O_WRONLY | O_APPEND);
    rt->fdModifier(-1,fds);
    
    curr = new Pipe(curr,rt);
    
	ASSERT_TRUE(curr->Execute() > 0);
}

TEST(PipeExecutionTests, Pipe_Success3) {
    parser userCommand("cat < out.txt | sort | tr a-z A-Z");
    std::vector<char**> userInput = userCommand.parse();
    Base* curr = new Command(userInput.at(0)),* rt = new Command(userInput.at(4));
    
    char* fileName = userInput.at(2)[0];
    
    int fds = open(fileName, O_RDONLY);
    curr->fdModifier(fds,-1);
    
    curr = new Pipe(curr,rt);
    rt = new Command(userInput.at(6));
    curr = new Pipe(curr,rt);
    
	ASSERT_TRUE(curr->Execute() > 0);
}

#endif