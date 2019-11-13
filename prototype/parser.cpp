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
        //comments
        if(user_input.at(currLoc) == '#') {
            commands.push_back(buildSingleCommand(pre));
            return commands;
        }
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