#ifndef _OR_H_
#define _OR_H_

#include "CNT.h"



class OR : public Connector{

	public:
		OR(Base* lf,Base* rf);
	    virtual pid_t Execute();
	    virtual void fdModifier(int newFdIn, int newFdOut);

};

#endif