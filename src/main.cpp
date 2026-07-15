#include "lua/lua_env.hpp"
#include "lua/init_lua_modules.h"
#include "utils/file_sys.h"
#include "lua/utils/converters.h"
#include "console/console_wrapper.hpp"
#include "render/main_render.h"

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

    // get the term control LUA_TABLE from cfg file
    auto control_table = lua::do_file<sol::table>(
        util::path({ paths["cfg_path"], "cfg_control_codes.lua" }),
        lua::get_state(lua::states::server)
    );
    // convert this table and fill the "control_map" hash map in console_wrapper.h with it
    term::control_map = lua::table_to_hash(control_table);


    // === RUN ENGINE LOGIC ===
    term::msg("Hello", "World\n",
    "Engine CFG and TESTs: \n\n",
    term::get_ansi("error"),"hello in red", term::get_ansi("reset"), "\n");

    term::msg("ANSI-code map include: ", std::to_string(term::ansi.size()), "\n");
    term::msg("Control-code map include: ", std::to_string(term::control_map.size()), "\n");

    term::ask("Press Enter to continue");
    lua::do_file("on_engine_init.lua", lua::get_state(lua::states::server));


    // === RUN BLUEPRINT LOGIC ===


    // === TEST LOGIC ===
    render::init(600, 400, "Debug");
    while (render::is_open()){
        render::update();
    }

    term::ask("\nEnter to quit");
    return 0;
}
