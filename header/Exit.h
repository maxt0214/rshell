#ifndef _EXIT_H_
#define _EXIT_H_

#include "CMD.h"

#include <unistd.h>
#include <stdio.h>

class Exit : public Command {
    public:
        Exit(char** user_Command);
        virtual pid_t Execute();
        virtual void fdModifier(int newFdIn, int newFdOut);
};

#endif