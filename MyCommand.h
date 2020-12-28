#ifndef __MY_COMMAND_H
#define __MY_COMMAND_H

#include <MyPlatform.h>

class MyCommand
{
    private:
        struct Token {
            std::string text;
            size_t      index;
        };

        char*              CompletionGenerator(const char* text, int state);
        static char**      Completion(const char* text, int start, int end);
        static char*       StaticCompletionGenerator(const char* text, int state);
        std::vector<Token> TokenizeLine(const std::string& buf); 

    public:
                MyCommand();
        virtual ~MyCommand();
        int     Run(int argc, char** argv);
};

#endif /* __MY_COMMAND_H */