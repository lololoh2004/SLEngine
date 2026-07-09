#include "glua/lua_env.hpp"
#include "glua/init_lua_modules.h"
#include "utils/file_sys.h"
#include "glua/utils/converters.h"

int main() {
    term::clear();

    // === LUA INIT AND VARS ===
    lua::init_state();
    sol::state& server_state = lua::get_state(lua::states::server);
    lua::do_file("on_lua_init.lua", lua::get_state(lua::states::server));

    // lua api bindings
    lua::base::init_base_api(server_state);

    // load file paths cfg
    auto engine_paths_table = lua::do_file<sol::table>("cfg_paths.lua", server_state);
    std::unordered_map paths = lua::table_to_hash(engine_paths_table);


    // === CFG and POST-INIT LOGIC ===
    // get the style LUA_TABLE from cfg file
    auto ansi_table = lua::do_file<sol::table>(
        util::path({ paths["cfg_path"], "cfg_ansi_codes.lua" }),
        lua::get_state(lua::states::server)
    );
    // convert this table and fill the "ansi" hash map in console_wrapper.h with it
    term::ansi = lua::table_to_hash(ansi_table);
    term::msg("ANSI-code map include: ", std::to_string(term::ansi.size()), "\n");
    // test text using this hash map
    term::msg("Hello", "World\n",
    "Engine CFG and TESTs: \n\n",
    term::get_ansi("error"),"hello in red", term::get_ansi("reset"), "\n");


    // === RUN LOGIC ===
    lua::do_file("on_engine_init.lua", lua::get_state(lua::states::server));

    term::ask("\nEnter to quit");
    return 0;
}
