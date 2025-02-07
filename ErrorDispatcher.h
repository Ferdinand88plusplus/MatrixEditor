#pragma once
#include <iostream>
#include <conio.h>

namespace ErrorDispatcher{
    inline void Throw(const std::string& errsrc, const std::string& errormsg){
        std::cerr<<"Error handled from ["<<errsrc<<"]: \""<<errormsg<<"\"\n";

        std::cerr<<"Press SPACE to send SIGTRAP, or any other key to close program.\n";

        if(_getch() == ' '){
            __debugbreak();
        }

        exit(EXIT_FAILURE);
    }
}