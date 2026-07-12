#include "console_additions.h"
#include "console_wrapper.hpp"
#include <conio.h>

namespace term{
    void progress_bar(double current, double total){
        float progress = current / total;

        short unsigned int bar_width = 10;
        short unsigned int filled = progress * bar_width;
        short unsigned int empty = bar_width - filled;

        std::cout << "\r[" << std::string(filled, '#') << std::string(empty, ' ') << "]" << progress * 100.0f << "%                  " << std::flush;
    }

    // [[nodiscard]] size_t pick(std::string_view title, const std::span<const std::string> options){
    //     size_t selected_index = 0;
    //
    //     while (true){
    //         clear();
    //         msg(title, "\n");
    //         size_t i = 0;
    //
    //         for (const auto& option : options){
    //             const char* prefix = i == selected_index ? "\n> " : "\n  ";
    //             msg(prefix, option);
    //             i++;
    //         }
    //
    //         short unsigned int input = _getch();
    //         if (input == 224) {
    //             switch (_getch()) {
    //                 case 72: if (selected_index > 0) selected_index--;break;
    //                 case 80: if (selected_index < options.size() -1 ) selected_index++; break;
    //                 default: break;
    //                 // 75 left, 77 right
    //             }
    //         } else if (input == 13) {
    //             return selected_index;
    //         }
    //     }
    // }
}