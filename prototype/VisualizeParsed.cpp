#include "parser.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
    string user_input;
    
    do {
        cout << "$ ";
        getline(cin,user_input);
    
        parser userCommand(user_input);
        vector<char**> commands = userCommand.parse();
        
        for(unsigned i = 0; i < commands.size(); i++) {
            char** args = commands.at(i);
        
            int j = 0;
            while(args[j] != NULL) {
                cout << args[j] << "//";
                j ++;
            }
            cout << endl;
        }
    } while(user_input != "q");
    
    return 0;
}