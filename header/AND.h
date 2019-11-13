#ifndef _AND_H_
#define _AND_H_

#include "CNT.h"

class AND : public Connector{
	public:
		AND(Base* lf, Base* rt);
	    virtual pid_t Execute();

};

#endif