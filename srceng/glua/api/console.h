#pragma once

#include <string_view>
#include <sol/sol.hpp>

namespace lua::console{
    void pro_print(std::string_view style1, std::string_view style2, sol::variadic_args va);
}
