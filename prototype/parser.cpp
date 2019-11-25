#include "parser.h"

#include <vector>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

std::vector<char**> parser::parse() {
    std::vector<char**> commands;
    unsigned pre = 0;
    string previousCommand;
    
    /*
        Goal: Build a vector of commands and connectors. Ex: {"command 1", "connector", "command2", etc}
        
        > find the connector
        > use buildSingleCommand to build command in the range of pre and curr, and push it to commands
        > build a array of connector cstring and push to commands
        > set pre to curr
        > if reach end of user input, build the last command using pre and curr, and push
    */
    
    while(currLoc < user_input.size()) {
        
        if(user_input.at(currLoc) == '#') { //comments
            //push back the previous command
            previousCommand = user_input.substr(pre, currLoc - pre);
            if(previousCommand.size() != 0 && previousCommand != " ") {
                commands.push_back(buildSingleCommand(previousCommand));
            }
            return commands;
        }
        
        if(user_input.at(currLoc) == ';' || user_input.at(currLoc) == '(' || user_input.at(currLoc) == ')' || 
           user_input.at(currLoc) == '[' || user_input.at(currLoc) == ']') { //connector ; ( ) or test command []
            
            //push back the previous command
            previousCommand = user_input.substr(pre, currLoc - pre);
            if(previousCommand.size() != 0 && previousCommand != " ") {
                commands.push_back(buildSingleCommand(previousCommand));
            }
            //move two counters: now pre should be pointing to ;()[] and currLoc should point to the one next to ;()[]
            pre = currLoc;
            currLoc ++;
            //push back ';'
            previousCommand = user_input.substr(pre, currLoc - pre);
            commands.push_back(buildSingleCommand(previousCommand));
            //now pre should point to the one next to ;()[], which is currLoc
            pre ++;
            currLoc --;
        }
        
        if(currLoc + 1 < user_input.size()) {//check if out of bound
            if( (user_input.at(currLoc) == '&' && user_input.at(currLoc+1) == '&') ||
                (user_input.at(currLoc) == '|' && user_input.at(currLoc+1) == '|') ) { //connector && or ||
           
                //push back the previous command
                previousCommand = user_input.substr(pre, currLoc - pre);
                if(previousCommand.size() != 0 && previousCommand != " ") {
                    commands.push_back(buildSingleCommand(previousCommand));
                }
                //move two counters: now pre should be pointing to first & and currLoc should point to the one next to &&
                pre = currLoc;
                currLoc += 2;
                //push back &&
                previousCommand = user_input.substr(pre, currLoc - pre);
                commands.push_back(buildSingleCommand(previousCommand));
                //now pre should point to the one next to &&, which is currLoc
                pre += 2;
                currLoc --;
            }
        }
        
        if(currLoc + 3 < user_input.size()) {//check if out of bound
            if(user_input.at(currLoc) == 't' && user_input.at(currLoc+1) == 'e' &&
               user_input.at(currLoc+2) == 's' && user_input.at(currLoc+3) == 't') { //command test
           
                //push back the previous command
                previousCommand = user_input.substr(pre, currLoc - pre);
                if(previousCommand.size() != 0 && previousCommand != " ") {
                    commands.push_back(buildSingleCommand(previousCommand));
                }
                //move two counters: now pre should be pointing to first t and currLoc should point to the one next to test
                pre = currLoc;
                currLoc += 4;
                //push back test
                previousCommand = user_input.substr(pre, currLoc - pre);
                commands.push_back(buildSingleCommand(previousCommand));
                //now pre should point to the one next to test, which is currLoc
                pre += 4;
                currLoc --;
            }
        }
        
        if(currLoc + 1 == user_input.size()) { //reach the end, build the last command
            previousCommand = user_input.substr(pre, currLoc + 1 - pre);
            if(previousCommand.size() != 0 && previousCommand != " ") {
                commands.push_back(buildSingleCommand(previousCommand));
            }
        }
        //update currLoc
        currLoc ++;
    }
    
    return commands;
}

char** parser::buildSingleCommand(string singleCommand) {
    char** command = new char*[20];
    unsigned commandIndex = 0;
    
    char* input = new char[100];
    unsigned counter = 0;
    
    for(unsigned i = 0; i < singleCommand.size() ; i++) {
        input[counter] = singleCommand.at(i);
        counter ++;
    }
    input[counter] = '\0';
    
    char* parsed = strtok(input," ");
    while(parsed != NULL) {
        command[commandIndex] = parsed;
        commandIndex ++;
        
        parsed = strtok(NULL," ");
    }
    command[commandIndex] = NULL;
    
    return command;
}