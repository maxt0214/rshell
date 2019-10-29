#include <iostream>

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

using namespace std;

#include "parser.h"

//Tests for waitpid(), execvp() and fork()
void exeCommand(char** command) {
    pid_t c_pid;
    int status;
    
    c_pid = fork();
    
    if(c_pid == 0) { //child process
        execvp(command[0],command);
        cout << "Execute command failed." << endl;
    } else if(c_pid > 0) { //parent process
        waitpid(c_pid, &status, WUNTRACED);
    } else { //fork failed
        cout << "Fork failed." << endl;
    }
}

int main() {
    parser userCommand("ls -a -l");
    
    char** args = userCommand.parse().at(0);
    
    int i = 0;
    
    while(args[i] != NULL) {
        cout << args[i] << " ";
        i ++;
    }
    cout << endl;
    
    exeCommand(args);
    
    return 0;
}

