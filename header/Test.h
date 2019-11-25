#ifndef _TEST_H_
#define _TEST_H_

#include "CMD.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

class Test : public Command{
    protected:
        char* flag;
        string& filePath;

    public:
        Test(char** pathDirectory);
        bool Execute();
};

#endif