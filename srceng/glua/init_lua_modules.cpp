#include "init_lua_modules.h"

#include "lua_env.hpp"
#include "api/console.h"
#include "utils/file_sys.h"

namespace lua::base{
    void init_base_api(sol::state& state){
        // Table tree API structure
        sol::table api = state["api"].get_or_create<sol::table>();
        sol::table console = api["console"].get_or_create<sol::table>();
        sol::table util_table = state["util"].get_or_create<sol::table>();
        // Functions
        console["pro_print"] = &lua::console::pro_print;
        util_table["system_launch"] = &util::launch;
    }
}
