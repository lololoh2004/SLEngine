#include "console.h"
#include <sol/sol.hpp>
#include "console/console_wrapper.hpp"

namespace lua::lua_term{
    void pro_print(std::string_view style1, std::string_view style2, sol::variadic_args va){
        std::string result;

        result += term::get_ansi(style1);
        result += term::get_ansi(style2);

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
    size_t lua_pick(std::string_view header, sol::table options){
        size_t selected = 0;

        while (true){
            term::clear();
            term::msg(header, "\n");

            size_t i=0;
            for (const auto& option : options){
                std::string prefix        = i == selected ? "> " :"  ";
                std::string option_header = option.first.is<std::string>() ?
                                            option.first.as<std::string>() :
                                            std::to_string(i);
                std::string description   = option.second.is<std::string>() ?
                                            option.second.as<std::string>() :
                                            "WARN : NO_STRING_DESCRIPTION";
                term::msg(prefix, option_header, "\n   ",description, "\n");
                i++;
            }
            std::string choice = term::get_key();
            if (choice == "up" && selected > 0)
                selected--;
            if (choice == "down" && selected < i - 1)
                selected++;
            if (choice == "enter"){
                term::clear() ; return selected;
            }
        }
    }
}
