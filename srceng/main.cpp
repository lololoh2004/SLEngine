#include "glua/lua_env.hpp"
#include "console/console_wrapper.hpp"

// #include "console/console_additions.h"

int main() {
    console::clear();
    console::msg("Hello", "World");
    // sol::table config = lua::do_file<sol::table>("config.lua");
    // int result = lua::table_value<int>(config, "width");
    // console::msg(result);

    lua::do_file("config.lua", lua::get_state(lua::states::server));
    //console::msg(table.get<std::string>());
    console::ask("\nEnter to quit");

    return 0;
}
