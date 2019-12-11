#include "../header/pipe.h"
#include "../header/CNT.h"

#include <iostream>

Pipe::Pipe(Base* leftChild, Base* rightChild) : Connector(leftChild,rightChild) {}

pid_t Pipe::Execute(){
	int fds[2];
	
	if(pipe(fds) < 0) {
		perror("pipe");
        return -1;
	}
	
	childLeft -> fdModifier(-1,fds[1]);
	if(childLeft -> Execute() == -1) {
		return -1;
	}
	
	close(fds[1]);
	
	childRight -> fdModifier(fds[0],-1);
	//modify the fdOut if the fdOut of the current pipe is not -1
	if(fdOut != -1) {
		childRight -> fdModifier(-1,fdOut);
	}
	
	int returnValue = childRight -> Execute();
	
	close(fds[0]);
	
	return returnValue;
}

void Pipe::fdModifier(int newFdIn, int newFdOut){
	if(newFdIn != -1) {
		this -> fdIn = newFdIn;
	}
	if(newFdOut != -1) {
		this -> fdOut = newFdOut;
	}
}