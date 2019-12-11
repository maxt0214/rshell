#include "../prototype/parser.h"
#include "../header/Base.hpp"
#include "../header/CMD.h"
#include "../header/Exit.h"
#include "../header/AND.h"
#include "../header/OR.h"
#include "../header/SEMI.h"
#include "../header/Test.h"
#include "../header/pipe.h"

#include <string>
#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <vector>
#include <fstream>

using namespace std;

Base* GenerateSingleCommand(char** currCommand, int& currLoc, int end);
Base* GenerateCommands(vector<char**> commands, int start, int end); //generate either test, command, or exit
int searchParenthesis(vector<char**> commands, unsigned start);
vector<char**> parseRedirection(string toParse);

int main() {
    string userInput;
    
    do {
        //prompt the user and get the input
        cout << "$ ";
        getline(cin, userInput);
        //set up the parsed commands
        parser parsedInput(userInput);
        vector<char**> commands = parsedInput.parse();
        
        //check if no commands input by user
        if(commands.size() != 0) {
            //Set up the commands and execute
            Base* executableCommand = GenerateCommands(commands, 0, commands.size()-1);
            if(executableCommand == NULL) {
                cout << "Syntax Error!" << endl;
            } else {
                executableCommand->Execute();
            }
            //free memories
            for(unsigned i = 0; i < commands.size(); i++) {
                delete[] commands.at(i);
            }
        }
    } while(!cin.fail());
}

Base* GenerateSingleCommand(vector<char**> commands, int& currLoc, int end) {
    Base* curr;
    char** currCommand = commands.at(currLoc);
    
    if(currCommand == NULL) {
        return NULL;
    }
    
    string temp = currCommand[0];
    
    if(temp == "(") {//search for ) to continue
        int final = searchParenthesis(commands, currLoc);
        if(final == 0) {//error
            return NULL;
        } else {
            curr = GenerateCommands(commands,currLoc+1,final-1);
            if(curr == NULL) {//syntax error in 
                return NULL;
            }
        }
        //update currLoc
        currLoc = final;
    } else if(temp == "[") {//search for ] to continue
        
        if(currLoc + 2 <= end) {// [ something ]
            string checkBracket = commands.at(currLoc+2)[0];
            if(checkBracket == "]") {
                char** testCommand = commands.at(currLoc+1);
                curr = new TestCmd(testCommand);
            } else {
                return NULL;
            }
        } else {
            return NULL;
        }
        currLoc += 2;
    } else if(temp == "]" && temp == ")" || temp == "&&" || temp == "||" || temp == ";") {//syntax error
        return NULL;
    } else if(temp == "test") {
        
        if(currLoc + 1 > end) {//only contains a "test"
            return NULL;
        } else {//have something other than "test"
            currLoc ++; //discard test
            currCommand = commands.at(currLoc);
            curr = new TestCmd(currCommand);
        }
        
    } else if(temp == "exit") {
        curr = new Exit(currCommand);
    } else {//normal command
        curr = new Command(currCommand);
    }
    //update currLoc to the command after the previous constructed one
    currLoc ++;
    
    
    //check if any redirection
    if(currLoc >= commands.size()) { //check if any more commands
        temp = "";
    } else {
        temp = commands.at(currLoc)[0];
    }
    
    while(temp == ">>" || temp == "<" || temp == ">") {
        if(temp == ">>") {
            if(currLoc+1 >= commands.size()) { //nothing after >> or >
                return NULL;
            }
            char* fileName = commands.at(currLoc+1)[0];
            
            int fds = open(fileName, O_WRONLY | O_APPEND);
            if(fds < 0) { //not exsited
                string filename = fileName;
                ofstream newFile(filename);
                newFile.close();
                fds = open(fileName, O_WRONLY | O_APPEND);
            }
            curr->fdModifier(-1,fds);
            currLoc += 2; //jump to the command after the filename
        }
    
        if(temp == ">") {
            if(currLoc+1 >= commands.size()) { //nothing after >> or >
                return NULL;
            }
            char* fileName = commands.at(currLoc+1)[0];
            
            string filename = fileName;
            ofstream newFile;
            newFile.open(fileName,std::ofstream::out | std::ofstream::trunc);
            newFile.close();
        
            int fds = open(fileName, O_WRONLY | O_APPEND);
            //change the fd of the previous command
            curr->fdModifier(-1,fds);
            currLoc += 2; //jump to the command after the filename
        } 
        
        if(temp == "<") {
            if(currLoc+1 >= commands.size()) { //nothing after <
                return NULL;
            }
            char* fileName = commands.at(currLoc+1)[0];
            //create new fd
            int fds = open(fileName, O_RDONLY);
            if(fds < 0) { //not exsited
                cout << "File not exsited" << endl;
                return NULL;
            }
            curr->fdModifier(fds,-1);
            currLoc += 2; //jump to the command after the filename
        }
        //get the command after the filename to see if it's another redirection
        if(currLoc >= commands.size()) { //check if any more commands
             temp = "";
        } else {
            temp = commands.at(currLoc)[0];
        }
    }
    
    return curr;
}

Base* GenerateCommands(vector<char**> commands, int start, int end) {
    Base* lf,* mid,* rt;
    int currLoc = start;
    
    lf = GenerateSingleCommand(commands, currLoc, end);
    
    while(currLoc <= end) {//if executed, currLoc now should point to the middle connector
        if(currLoc + 1 > end) {//check if there is a right command
            return NULL;
        }
        
        char** currCommand = commands.at(currLoc);
        string temp = currCommand[0];
        //mid connector
        if(temp == "(" || temp == ")" || temp == "[" || temp == "]") {//error, should only be a connector
            return NULL;
        } else if(temp == "&&") {
            currLoc ++;
            rt = GenerateSingleCommand(commands, currLoc, end);
            mid = new AND(lf,rt);
        } else if(temp == "||") {
            currLoc ++;
            rt = GenerateSingleCommand(commands, currLoc, end);
            mid = new OR(lf,rt);
        } else if(temp == ";") {
            currLoc ++;
            rt = GenerateSingleCommand(commands, currLoc, end);
            mid = new SEMI(lf,rt);
        } else if(temp == "|") {
            currLoc ++;
            rt = GenerateSingleCommand(commands, currLoc, end);
            mid = new Pipe(lf,rt);
        } else {//the middle is not connector, error
            return NULL;
        }
        
        lf = mid;
    }
    
    return lf;
}

int searchParenthesis(vector<char**> commands, unsigned start) {
    char** currCommand;
    string ifparenthesis;
    int additionalParenthesis = 0, MatchLoc = 0;
    for(int i = start+1; i < commands.size(); i ++) {
        currCommand = commands.at(i);
        ifparenthesis = currCommand[0];
        //check for additional ( on the way searching for )
        if(ifparenthesis == "(") {
            additionalParenthesis ++;
        }
        if(ifparenthesis == ")") {
            if(additionalParenthesis > 0) { //skip for the )'s matching for other (
                additionalParenthesis--;
            } else {
                return i;
            }
        }
    }
    //0 means not found, otherwise found
    return MatchLoc;
}