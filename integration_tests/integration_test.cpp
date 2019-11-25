#include "../prototype/parser.h"
#include "../header/Base.hpp"
#include "../header/CMD.h"
#include "../header/Exit.h"
#include "../header/AND.h"
#include "../header/OR.h"
#include "../header/SEMI.h"

#include <string>
#include <vector>

using namespace std;

Base* GenerateSingleCommand(char** currCommand, int& currLoc, int end);
Base* GenerateCommands(vector<char**> commands, int start, int end); //generate either test, command, or exit
int searchParenthesis(vector<char**> commands, unsigned start);

int main() {
    string userInput;
    
    getline(cin,userInput);
    
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
}

Base* GenerateSingleCommand(vector<char**> commands, int& currLoc, int end) {
    Base* curr;
    char** currCommand = commands.at(currLoc);
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
        
    } else if(temp == "]" && temp == ")" || temp == "&&" || temp == "||" || temp == ";") {//syntax error
        return NULL;
    } else if(temp == "test") {
        
        if(currLoc + 1 > end) {//only contains a "test"
            
        } else {//have something other than "test"
            currLoc ++; //discard test
            currCommand = commands.at(currLoc);
            temp = currCommand[0];
            
            if(temp == "&&" || temp == "||" || temp == ";") {// input is: test && || ; ...
                
            } else {// input is: test ...
                
            }
        }
        
    } else if(temp == "exit") {
        curr = new Exit(currCommand);
    } else {//normal command
        curr = new Command(currCommand);
    }
    //update currLoc
    currLoc ++;
    
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
        } else {//the middle connector is test, error
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