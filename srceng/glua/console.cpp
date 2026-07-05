#include "console.h"
#include "lua_env.hpp"
#include "utils/other.h"

namespace lua::console{
    void pro_print(std::string_view style1, std::string_view style2, sol::variadic_args va){
        std::string result;

        result += term::get_ansi(util::to_lower(style1));
        result += term::get_ansi(util::to_lower(style2));

        for (const auto& obj : va){
            sol::type obj_type = obj.get_type();
            switch (obj_type){
                case sol::type::string:
                    result += obj.as<std::string>(); break;
                case sol::type::number:
                    result += std::to_string(obj.as<double>()); break;
                case sol::type::boolean:
                    result += (obj.as<bool>() ? "true" : "false");  break;
                case sol::type::nil:
                    result += "nil"; break;
                default: break;
            }
            result += " ";
        }
        term::msg(result, "\x1b[0m","\n");
    }
}
