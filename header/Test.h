#ifndef _TEST_H_
#define _TEST_H_

#include "Base.hpp"
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

class TestCmd : public Base {
    protected:
        char flag;
        char* filePath;

    public:
        TestCmd(char** pathDirectory);
        virtual pid_t Execute();
};

#endif