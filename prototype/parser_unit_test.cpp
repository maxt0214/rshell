#include "parser.h"

#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

void printCommands(vector<char**> testCommands);

int main() {
    
    vector<char**> testCommands;
    //test case 1: single command
    parser command_single("ls -a");
    testCommands = command_single.parse();
    cout << "Test case 1: ";
    printCommands(testCommands);
    //test case 2: multiple commands with simcolon
    parser command_simcolon("ls -a ; ls");
    testCommands = command_simcolon.parse();
    cout << "Test case 2: ";
    printCommands(testCommands);
    //test case 3: multiple commands with &&
    parser command_and("ls -a && ls");
    testCommands = command_and.parse();
    cout << "Test case 3: ";
    printCommands(testCommands);
    //test case 4: multiple commands with ||
    parser command_or("ls -a || ls");
    testCommands = command_or.parse();
    cout << "Test case 4: ";
    printCommands(testCommands);
    //test case 5: multiple commands with three connectors
    parser command_multiple("ls -a ; ls && mkdir myfolder || echo hello ; git status");
    testCommands = command_multiple.parse();
    cout << "Test case 5: ";
    printCommands(testCommands);
    
    return 0;
}

void printCommands(vector<char**> testCommands) {
    for(unsigned i = 0; i < testCommands.size(); i++) {
        char** currCommand = testCommands.at(i);
        int counter = 0;
        while(currCommand[counter] != NULL) {
            cout << currCommand[counter] << " ";
            counter ++;
        }
    }
    cout << endl;
}