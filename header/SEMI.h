#ifndef _SEMI_H_
#define _SEMI_H_

#include "CNT.h"

class SEMI : public Connector{
	public:
		SEMI(Base* lf,Base* rf);
	    virtual pid_t Execute();
};

#endif