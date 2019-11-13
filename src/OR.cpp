#include "../header/OR.h"

OR::OR(Base* lf,Base* rf) : Connector(lf,rf) {}

pid_t OR::Execute(){
	int processID = childLeft -> Execute();
	
	if(processID == -1)
		return childRight -> Execute();
	else 
		return processID;
}