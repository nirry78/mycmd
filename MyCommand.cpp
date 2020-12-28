#include "MyCommand.h"

static MyCommand *myCommand = NULL;

MyCommand::MyCommand()
{

}

MyCommand::~MyCommand()
{

}

char** MyCommand::Completion(const char* text, int start, int end)
{
    // Don't do filename completion even if our generator finds no matches.
    rl_attempted_completion_over = 1;

    // Note: returning nullptr here will make readline use the default filename
    // completer.
    return rl_completion_matches(text, StaticCompletionGenerator);    
}

char* MyCommand::CompletionGenerator(const char* text, int state)
{
    /* https://github.com/eliben/code-for-blog/tree/master/2016/readline-samples */
    std::vector<Token> line_tokens = TokenizeLine(rl_line_buffer);
}

char* MyCommand::StaticCompletionGenerator(const char* text, int state)
{
    if (myCommand)
    {
        return myCommand->CompletionGenerator(text, state);
    }

    return NULL;
}

std::vector<MyCommand::Token> MyCommand::TokenizeLine(const std::string& buf) 
{
    const char* delims = " \t";
    std::vector<Token> tokens;

    // Skip leading delimiters to the first token.
    size_t istart = buf.find_first_not_of(delims);
    while (istart != std::string::npos) 
    {
        // Invariant: istart points at the beginning of a token inside buf.
        size_t iend = buf.find_first_of(delims, istart);
        if (iend == std::string::npos) 
        {
            iend = buf.size();
        }

        tokens.push_back({buf.substr(istart, iend - istart), istart});
        istart = buf.find_first_not_of(delims, iend);
    }

    return tokens;
}

int MyCommand::Run(int argc, char** argv)
{
    rl_attempted_completion_function = Completion;

    return 0;
}

int main(int argc, char **argv)
{
    int result = 2;

    try
    {
        myCommand = new MyCommand();
        if (myCommand)
        {
            result = myCommand->Run(argc, argv);
            delete myCommand;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return result;
}
