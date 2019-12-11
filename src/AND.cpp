#include "../header/AND.h"

#include <unistd.h>

AND::AND(Base* lf,Base* rf) : Connector(lf,rf) {}

pid_t AND::Execute(){
	
	if(childLeft -> Execute() != -1)  {
		childRight -> fdModifier(fdIn, fdOut);
		return childRight -> Execute();
	} else {
		return -1; 
	}
}

void AND::fdModifier(int newFdIn, int newFdOut){
	if(newFdIn != -1) {
		this -> fdIn = newFdIn;
	}
	if(newFdOut != -1) {
		this -> fdOut = newFdOut;
	}
}