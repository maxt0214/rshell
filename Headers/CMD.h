#ifndef _CMD_H_
#define _CMD_H_

#include "Base.hpp"

#include <unistd.h>
#include <stdio.h>

class Command : public Base {
    private:
        char** command;
    public:
        Command(char** user_Command);
        virtual pid_t Execute();
};

#endif