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
    /* https://github.com/eliben/code-for-blog/tree/master/2016/readline-samples */
    std::vector<Token> lineTokens = myCommand->TokenizeLine(rl_line_buffer);
    auto command = myCommand->FindCommand(lineTokens, start);

    // Don't do filename completion even if our generator finds no matches.
    rl_attempted_completion_over = 1;

    std::cout << "[" << lineTokens.size() << " tokens]: ";
    for (const auto& t : lineTokens)
    {
        std::cout << t.text << "[" << t.index << "] ";
    }
    std::cout << "\n";

    return nullptr;
#if 0
    // Don't do filename completion even if our generator finds no matches.
    rl_attempted_completion_over = 1;

    // Note: returning nullptr here will make readline use the default filename
    // completer.
    return rl_completion_matches(text, StaticCompletionGenerator);
#endif
}

char* MyCommand::CompletionGenerator(const char* text, int state)
{
#if 0
    /* https://github.com/eliben/code-for-blog/tree/master/2016/readline-samples */
    std::vector<Token> lineTokens = TokenizeLine(rl_line_buffer);
    std::string command = FindCommand(lineTokens, start);

    std::cout << "[" << lineTokens.size() << " tokens]: ";
    for (const auto& t : lineTokens)
    {
        std::cout << t.text << "[" << t.index << "] ";
    }
    std::cout << "\n";
#endif
    return nullptr;
}

std::string MyCommand::FindCommand(const std::vector<Token>& tokens, int cursor)
{
    if (tokens.size() == 0)
    {
        return "";
    }

    const Token& command = tokens[0];
    if (static_cast<size_t>(cursor) > command.index + command.text.size())
    {
        return command.text;
    }
    else
    {
        return "";
    }
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
    char* buf;

    rl_attempted_completion_function = Completion;

    while ((buf = readline("mycmd:> ")) != nullptr)
    {
        if (buf[0] != 0)
        {
            add_history(buf);
        }

        free(buf);
    }

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
