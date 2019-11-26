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
        execvp(command[0],command);
        cout << "! Command not found" << endl;//print only if execution fails
        exit(1); //pass the flag that execution failed to the parent process
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