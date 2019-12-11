#include "../header/OR.h"

OR::OR(Base* lf,Base* rf) : Connector(lf,rf) {}

pid_t OR::Execute() {

	childLeft -> fdModifier(fdIn, fdOut);
	int processID = childLeft -> Execute();
	
	if(processID == -1) {
		childRight -> fdModifier(fdIn, fdOut);
		return childRight -> Execute();
	} else {
		return processID;
	}
}

void OR::fdModifier(int newFdIn, int newFdOut){
	if(newFdIn != -1) {
		this -> fdIn = newFdIn;
	}
	if(newFdOut != -1) {
		this -> fdOut = newFdOut;
	}
}