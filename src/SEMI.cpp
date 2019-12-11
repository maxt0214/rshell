#include "../header/SEMI.h"

SEMI::SEMI(Base* lf,Base* rf) : Connector(lf,rf){}

pid_t SEMI::Execute(){
	childLeft -> Execute();
	childRight -> fdModifier(fdIn, fdOut);
	return childRight -> Execute();
}

void SEMI::fdModifier(int newFdIn, int newFdOut){
	if(newFdIn != -1) {
		this -> fdIn = newFdIn;
	}
	if(newFdOut != -1) {
		this -> fdOut = newFdOut;
	}
}