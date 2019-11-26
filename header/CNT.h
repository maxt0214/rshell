#ifndef _CNT_H_
#define _CNT_H_

#include <iostream>
#include "Base.hpp"
#include <unistd.h>
#include <stdio.h>


class Connector : public Base {

	protected:
		Base* childLeft;
		Base* childRight;

	public:
		Connector(Base* leftChild, Base* rightChild);
		virtual pid_t Execute() = 0;

};

#endif
