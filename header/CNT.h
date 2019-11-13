#ifndef _CNT_H_
#define _CNT_H_

#include <iostream>
#include "Base.hpp"
#include <unistd.h>
#include <stdio.h>


class Connecter : public Base {

	private:
		Base* childLeft;
		Base* childRight;

	public:
		Connecter(Base* leftChild, Base* rightChild);
		virtual pid_t Execute() = 0;

};

#endif