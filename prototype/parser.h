#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>

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

#endif