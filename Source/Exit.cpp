#include "/home/ec2-user/environment/assignment-a1w_alums/Headers/Exit.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include <iostream>

using namespace std;

Exit::Exit(char** user_Command) : Command(user_Command) {
    this -> exitCommand = user_Command;
}

/*Exit::Execute is in charge for exiting the program
It the input is not exit, it would call command::execute to execute the command
Although it would check if the command passed in is exit and execute even if it's not exit,
don't pass in commands other than exit.*/

pid_t Exit::Execute() {
    char exitString[5] = "exit";
    if(*exitCommand[0] == *exitString) { //check if it is exit
        exit(0);
    }
    
    return Command::Execute();
}