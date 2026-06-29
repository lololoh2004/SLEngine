#pragma once

#if defined(_WIN32) || defined(_WIN64)
    // #include <windows.h>
    #include <conio.h>
// #elif defined(__linux__)
//     #include <unistd.h>
#endif

#include <iostream>

namespace console{

    inline void clear(){
        std::cout << "\033[H\033[2J" << std::flush;
    }

    inline char ask(std::string_view text){
        char temp;
        std::cout << text;
        std::cin.get(temp);
        return temp;
    }

    template <typename ... Args>
    void msg(Args&&... args){
        (std::cout << ... << args);
    }


}
