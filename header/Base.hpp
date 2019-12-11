#ifndef _BASE_HPP_
#define _BASE_HPP_

#include <unistd.h>
#include <stdio.h>

class Base {
   
	protected:
		int fdIn;
		int fdOut;

    public:
        Base() { fdIn = -1; fdOut = -1; };
        virtual pid_t Execute() = 0;
        virtual void fdModifier(int newFdIn, int newFdOut) = 0;
};

#endif