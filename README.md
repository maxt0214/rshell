# CS 100 Programming Project
- Ryan Lam, 862110744	                                                                                            		
- Xiaotian Ma, 862094705                                                            						
- CS100 Brian Crites - Fall 2019

**Introduction:**

We are currently using a composite design pattern to design our shell. Our project design consists of 6 classes which inherit from an interface in order to execute certain commands and functions. From our Base interface, we have two classes Connector and Command which allow for command execution based on the arguments and executables. From our connector class we have an AND, OR, and SEMICOLON class which are used to differentiate between single and several command executions. Furthermore, our EXIT class inherits from our Command class in order to follow specific procedures before exiting our shell. We added new feature supporting changes of the procedence of command execution by seperating them using parenthesis. Ex: (ls && pwd) || (echo && echo) will treat (ls && pwd) as the first command and (echo && echo) as the second command


**OMT Diagram:**
	
Our OMT diagram shows how we build composite pattern using multiple classes inherited from base class

![OMT Diagram](https://github.com/cs100/assignment-a1w_alums/blob/master/Images/Assignment%201%20UML.png?raw=true)

**Classes:**
	
1.*Base:*
Our Base class consists of a virtual execute function that will be inherited by all of our other classes. It will be used in order to support both connector and command execute functions. 

2.*Connector:*

Our Connector class will contain another virtual execute function that will allow for proper differentiation between a single and double command. For example, it will allow us to differentiate between calling two echo commands using a logical operator and a single command line. We will do this using a parser (code shown below) in order to compare characters and execute certain commands. 

Our AND class will only execute the right hand side command if the left hand side operator executes on through the parser. Furthermore, if the left hand side operator fails, either a flag will be set and an error will be output.

Our OR class will execute the right hand side command if the left hand side operator fails to do so. 

The Semicolon will allow for execution regardless of the use of an AND or OR, allowing for execution of multiple commands at a time. 

3.*Command:*
	
Our Command Class will use a value returned from the parser in order to execute specific commands.It will allow us to use functions such as waitpid(), fork(), and execvp() as well. 

Furthermore, our EXIT class will contain procedures among execution that will ensure that the command queue is empty and that there are no other commands being prompted after it. Shortly afterward, the command will execute and exit the shell. 

4.*Test:*
Our test command class currently allows the user to detect whether a file/directory exists with additional features using specific flags to do so, and uses the sys/stat library in order to verify the existence of certain files and data paths. The current flags correspond with each following operation:

 - -e	checks if the file/directory exists
 - -f	checks if the file/directory exists and is a regular file
 - -d	checks if the file/directory exists and is a directory

After the execution of the test command, the Terminal will output a boolean value (true) or (false) depending on the existence of the directory/file and flag being used. Additionally the shell allows for the use of brackets [] to operate a command as such: 

 - $ test -e test/file/path	- or -	$ [ -e test/file/path ]

 Executing the test command without a flag will automatically set the flag to -e. 


**Prototype**

Our prototype folder contains two parts, prototype functions to test execvp(), fork(), and waitpid(), and parser class to output a vector of  commands and connectors, ex: {command1, connector, command2, etc}. Commands and connectors are implemented as arrays of c-string. One single command could be {“ls”, ”-a”, “-l”}. Connector are implemented such as {“;”}, which only contain one string of connector. 

For the part how we could distinguish between multiple commands in one line or single command in one line, the returned vector of c-string arrays would only contain one array if the user only input single command, and vice versa. 

parser header:
```c++
class parser {
	private:
        	unsigned currLoc;
        	std::string user_input;
    	public:
        	parser(std::string user_input) { this->currLoc = 0; this->user_input = user_input; }
        	std::vector<char**> parse();
    	public:
        	char** buildSingleCommand(unsigned pre);
};
```
parser implementation:
```c++
#include "parser.h"

#include <vector>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

std::vector<char**> parser::parse() {
    std::vector<char**> commands;
    unsigned pre = 0;
    
    /*
        Goal: Build a vector of commands and connectors. Ex: {"command 1", "connector", "command2", etc}
        
        > find the connector
        > use buildSingleCommand to build command in the range of pre and curr, and push it to commands
        > build a array of connector cstring and push to commands
        > set pre to curr
        > if reach end of user input, build the last command using pre and curr, and push
    */
    
    while(currLoc < user_input.size()) {
        //connector ;
        if(user_input.at(currLoc) == ';') { 
            
            commands.push_back(buildSingleCommand(pre));
            //build a cstring of simcolon {';' , '\0'}
            char* simcolonChar = new char[2];
            simcolonChar[0] = user_input.at(currLoc);
            simcolonChar[1] = '\0';
            currLoc ++; //move to next
            //build a array of simcolon string {';' , NULL}
            char** simcolon = new char*[2];
            simcolon[0] = simcolonChar;
            simcolon[1] = NULL;
            commands.push_back(simcolon);
            //set pre to curr
            pre = currLoc;
        } 
        //connector && or ||
        if( (user_input.at(currLoc) == '&' && user_input.at(currLoc+1) == '&') || 
            (user_input.at(currLoc) == '|' && user_input.at(currLoc+1) == '|') ) { 
            
            commands.push_back(buildSingleCommand(pre));
            //build a cstring of simcolon {'&', '&', '\0'}
            char* AndOrString = new char[3];
            AndOrString[0] = user_input.at(currLoc);
            AndOrString[1] = user_input.at(currLoc+1);
            currLoc += 2; //move to next char because we append 2 chars
            AndOrString[2] = '\0';
            //build a array of simcolon string {'||' , NULL}
            char** AndOr = new char*[2];
            AndOr[0] = AndOrString;
            AndOr[1] = NULL;
            commands.push_back(AndOr);
            //set pre to curr
            pre = currLoc;
        }
        if(currLoc + 1 == user_input.size()) { //reach the end, build last command
            //adding one so buildSingleCommand can get whole command(currLoc points to the last char of command, which won't be visited)
            currLoc ++; 
            commands.push_back(buildSingleCommand(pre));
        }
        
        currLoc ++;//move to next char
    }
    
    return commands;
}

char** parser::buildSingleCommand(unsigned pre) {
    char** command = new char*[50];
    unsigned commandIndex = 0;
    char* input = new char[50];
    unsigned counter = 0;
    
    for(unsigned i = pre; i < currLoc && user_input.at(i) != '\0'; i++) {
        input[counter] = user_input.at(i);
        counter ++;
    }
    input[counter] = '\0';
    
    char* parsed = new char[50];
    parsed = strtok(input," ");
    while(parsed != NULL) {
        command[commandIndex] = parsed;
        commandIndex ++;
        
        parsed = strtok(NULL," ");
    }
    command[commandIndex] = NULL;
    
    return command;
}
```
prototype test
```c++
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
```
**Development and Testing Roadmap**

1. [x] Base Class                                 					@maxt0214
2. [x] CMD Class(concurrently with connector)						@maxt0214
3. [x] Unit_test for CMD Class								@maxt0214
4. [x] Connector Class									@rlam021
5. [x] Unit_test for Connector Class							@rlam021
6. [x] Exit Class									@maxt0214
7. [x] Unit_test for Exit Class								@maxt0214
8. [x] And Class									@rlam021
9. [x] Unit_test for And Class								@rlam021
10. [x] Or Class									@rlam021
11. [x] Unit_test for Or Class								@rlam021
12. [x] Semicolon Class									@rlam021
13. [x] Unit_test for Semicolon Class							@rlam021
14. [x] Integrated Tests								@maxt0214
15. [x] Test Command Implementation							@rlam021
16. [x] Test Command unit_test							        @rlam021
17. [x] Precedence Feature								@maxt0214
18. [x] Integrated Tests for test command and new precedence feature	                @maxt0214
19. [x] Pipe Class          								@rlam021
20. [x] CMD Class Update for I/O Redirection						@rlam021
21. [x] Unit tests for pipe and I/O redirection						@maxt0214
22. [x] Integrated tests for pipe and redirection					@maxt0214
	

