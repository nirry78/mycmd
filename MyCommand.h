#ifndef __MY_COMMAND_H
#define __MY_COMMAND_H

#include <MyPlatform.h>

class MyCommand
{

    public:
                MyCommand();
        virtual ~MyCommand();
        int     Run(int argc, char** argv);
};

#endif /* __MY_COMMAND_H */