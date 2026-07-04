#include "console/console_wrapper.hpp"
//#include "console/console_additions.h"
#include "glua/lua_env.hpp"
#include "utils/file_sys.h"


int main() {
    term::clear();

    // INIT AND VARS
    lua::init_state();
    sol::table engine_paths = lua::do_file<sol::table>("cfg_paths.lua", lua::get_state(lua::states::server));
    std::unordered_map engine_paths_map = lua::table_to_hash(engine_paths);

    std::string blueprints_path = engine_paths_map["blueprints_path"];
    std::string cfg_path = engine_paths_map["cfg_path"];

    // CFG and POST-INIT LOGIC LOGIC
    sol::table term_colors = lua::do_file<sol::table>(
        util::path({ cfg_path, "cfg_term_colors.lua" }).c_str(),
        lua::get_state(lua::states::server)
    );
    term::colors = lua::table_to_hash(term_colors);

    term::msg("Hello", "World\n",
    "You are on the Dev version of the branch.\n",
    "If you see this, you'd better leave.\n\n",
    "Engine CFG: \n\n",
    term::get_color("error"),"hello in red", term::get_color("reset"), "\n");

    term::ask("\nEnter to quit");
    return 0;
}
