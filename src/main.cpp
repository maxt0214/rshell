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

int main() {
    string userInput;
    vector<char**> commands;
    char exitString[7] = "exit";
    char semicolonString[2] = ";";
    char andString[3] = "&&";
    char orString[3] = "||";
    
    do {
        cout << "$ ";
        getline(cin,userInput);
        cout << endl;
        
        if(userInput.size() != 0) {
        
            //check if sytax error
            unsigned counter = 0;
            while(userInput.at(counter) == ' ') {
                counter ++;
            }
            
            if(userInput.at(counter) == ';' || userInput.at(counter) == '&' || userInput.at(counter) == '|' || userInput.at(counter) == '#') {
                cout << "Syntax error!" << endl;
            } else {
                parser parsedcommand(userInput);
                commands = parsedcommand.parse();
            }
        }
        
        if(commands.size() == 1) {//single command
            Exit* curr = new Exit(commands.at(0));
            curr->Execute();
        }
        
        if(commands.size() > 1) {//multiple commands
            Base* last = new Exit(commands.at(0));
            for(unsigned i = 1; i < commands.size() - 1; i++) {
                
                if(*commands.at(i) == semicolonString) {
                    SEMI* semiConnector = new SEMI(last,new Exit(commands.at(i+1)));
                    last = semiConnector;
                }
                
                if(*commands.at(i)[0] == *andString) {
                    AND* andConnector = new AND(last,new Exit(commands.at(i+1)));
                    last = andConnector;
                }
                
                if(*commands.at(i)[0] == *orString) {
                    OR* orConnector = new OR(last,new Exit(commands.at(i+1)));
                    last = orConnector;
                }
            }
            
            last->Execute();
        }
        
    } while(!cin.fail());
}