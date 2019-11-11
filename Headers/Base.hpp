#ifndef _BASE_HPP_
#define _BASE_HPP_

#include <unistd.h>
#include <stdio.h>

class Base {
    public:
        Base() {};
        virtual pid_t Execute() = 0;
};

#endif