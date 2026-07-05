#pragma once

#include <iostream>
#include <unordered_map>

namespace term{
    inline std::unordered_map<std::string, std::string> ansi;

    inline void clear(){
        std::cout << "\033[H\033[2J" << std::flush;
    }

    inline void ask(std::string_view text){
        std::cout << text << std::flush;
        while (std::cin.get() != '\n');
    }

    template <typename ... Args>
    void msg(Args&&... args){
        (std::cout << ... << args);
    }

    inline std::string get_ansi(std::string_view name ){
        auto i = ansi.find(std::string(name));
        if (i != ansi.end())
            return i->second;
        return "";
    }


}
