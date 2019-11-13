#include "../header/AND.h"

#include <unistd.h>

AND::AND(Base* lf,Base* rf) : Connector(lf,rf) {}

pid_t AND::Execute(){
	
	if(childLeft -> Execute() != -1)
		return childRight -> Execute();

	else
		return -1; 
}