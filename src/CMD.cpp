#include "../header/CMD.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include <iostream>

using namespace std;

Command::Command(char** user_Command) : Base() {
    this->command = user_Command;
}
//Command Execute only execute one command
//It would return the current pid
//If pid >= 0, it runs successfully. Else, it fails
pid_t Command::Execute() {
    pid_t c_pid;
    int status = -1;
    
    c_pid = fork();
    if(c_pid == 0) {//child process

        if(fdIn != -1){
            if(dup2(fdIn,0) == -1) {
                perror("dup2 fdIn");
                return -1;
            }
        }

        if(fdOut != -1){
            if(dup2(fdOut,1) == -1) {
                perror("dup2 fdIn");
                return -1;
            }
        }
        
        if (execvp(command[0],command) == -1) { //if anything goes wrong
            perror("! Command not found");
            exit(1); //pass the flag that execution failed to the parent process
        }
    } 
    if(c_pid > 0) {//parent process
        waitpid(c_pid, &status, WUNTRACED);
    }
    if(c_pid < 0) {//fork failed, error!
        perror("Fork Failed");
    }
    
    if(status/255 == 1) {//execution failed
        return -1;
    }
    return c_pid;
}

void Command::fdModifier(int newFdIn, int newFdOut){
    if(newFdIn != -1) {
		this -> fdIn = newFdIn;
	}
	if(newFdOut != -1) {
		this -> fdOut = newFdOut;
	}
}