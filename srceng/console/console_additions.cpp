#include "console_additions.h"

namespace console
{
    void progress_bar(double current, double total){
        float progress = current / total;

        short unsigned int bar_width = 10;
        short unsigned int filled = progress * bar_width;
        short unsigned int empty = bar_width - filled;

        std::cout << "\r[" << std::string(filled, '#') << std::string(empty, ' ') << "]" << progress * 100.0f << "%                  " << std::flush;
    }
}