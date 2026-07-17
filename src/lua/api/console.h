#pragma once

#include <string_view>
#include <sol/forward.hpp>

namespace lua::lua_term{
    void pro_print(std::string_view style1, std::string_view style2, sol::variadic_args va);
    size_t lua_pick(std::string_view header, sol::table options);
}
