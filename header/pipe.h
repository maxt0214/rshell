#ifndef _PIPE_H_
#define _PIPE_H_

#include "CNT.h"

class Pipe : public Connector {
	

	public:
		Pipe(Base* leftChild, Base* rightChild);
		virtual pid_t Execute();
		void fdModifier(int newFdIn, int newFdOut);

};

#endif