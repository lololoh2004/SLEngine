#include "console/console_wrapper.hpp"
//#include "console/console_additions.h"
#include "glua/console.h"
#include "glua/lua_env.hpp"
#include "utils/file_sys.h"

int main() {
    term::clear();


    // === INIT AND VARS ===
    lua::init_state();
    sol::state_view state = lua::get_state(lua::states::server);

    // lua paths
    sol::table api = state["api"].get_or_create<sol::table>();
    sol::table console = api["console"].get_or_create<sol::table>();
    sol::table util_table = state["util"].get_or_create<sol::table>();
    // lua functions
    console["pro_print"] = &lua::console::pro_print;
    util_table["system_launch"] = &util::launch;

    // load file paths cfg
    auto engine_paths = lua::do_file<sol::table>("cfg_paths.lua", lua::get_state(lua::states::server));
    std::unordered_map engine_paths_map = lua::table_to_hash(engine_paths);
    // create STRING vars with this cfg
    std::string bp_path = engine_paths_map["blueprints_path"]; // ALT NAME: just mods like in hl2
    std::string cfg_path = engine_paths_map["cfg_path"];

    // vector which include ALL folder names in bp_path
    std::vector bp_content_vector = util::directory_to_vector(bp_path.data(), util::scan_modes::only_folders);


    // === CFG and POST-INIT LOGIC ===
    // get the style LUA_TABLE from cfg file
    auto term_ansi_codes = lua::do_file<sol::table>(
        util::path({ cfg_path, "cfg_ansi_codes.lua" }).c_str(),
        lua::get_state(lua::states::server)
    );
    // convert this table and fill the "ansi" hash map in console_wrapper.h with it
    term::ansi = lua::table_to_hash(term_ansi_codes);
    term::msg("ANSI-code map include: ", std::to_string(term::ansi.size()), "\n");
    // test text using this hash map
    term::msg("Hello", "World\n",
    "You are on the Dev version of the branch.\n",
    "If you see this, you'd better leave.\n\n",
    "Engine CFG and TESTs: \n\n",
    term::get_ansi("error"),"hello in red", term::get_ansi("reset"), "\n");


    // === RUN LOGIC ===
    lua::do_file("on_engine_init.lua", lua::get_state(lua::states::server));

    // int bp_choice = term::pick("Choose Blueprint-Content", bp_content_vector);
    // term::msg("\n", bp_choice);

    term::ask("\nEnter to quit");
    return 0;
}
