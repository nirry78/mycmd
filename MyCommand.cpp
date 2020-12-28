#include "MyCommand.h"

MyCommand::MyCommand()
{

}

MyCommand::~MyCommand()
{

}

int MyCommand::Run(int argc, char** argv)
{
    return 0;
}

int main(int argc, char **argv)
{
    int result = 2;

    try
    {
        MyCommand *myCommand = new MyCommand();
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
