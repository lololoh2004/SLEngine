#pragma once
#include <string_view>

#include "console_wrapper.hpp"

namespace console
{
    void progress_bar(double current, double total);

    template <typename ... Args>
    short unsigned int pick(std::string_view title, Args&&... options){
        short unsigned int selected_index = 0;

        do{
            clear();
            std::cout << title << std::endl;
            short unsigned int i = 0;
            ((std::cout << (i++ == selected_index ? "-> " : "   ") << options << "\n"), ...);

            unsigned int input = _getch();
            if (input == 224){
                switch (_getch()){
                case 72: if (selected_index > 0) selected_index--;break;
                case 80: if (selected_index < sizeof...(options) - 1) selected_index++; break;
                default: break;
                }
            } else if (input == 13)
                return selected_index;
        }
        while (true);
    }
}
