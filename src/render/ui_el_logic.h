#pragma once
#include <string_view>

namespace render{
    void begin_window(std::string_view title);
    void add_text(std::string_view text);
    bool add_button(std::string_view text);
    void end_window();
}
