#include "init_lua_modules.h"

#include "lua_env.hpp"
#include "api/console.h"
#include "api/math.hpp"
#include "utils/file_sys.h"

namespace lua::base{
    void init_base_api(sol::state& state){
        // Table tree API structure
        sol::table api_table     = state["api"].get_or_create<sol::table>();
        sol::table math_table    = state["math"].get_or_create<sol::table>();
        sol::table util_table    = state["util"].get_or_create<sol::table>();
        sol::table console_table = state["console"].get_or_create<sol::table>();
        // Functions
        // From c++ term::...
        console_table["clear"] = &term::clear;
        console_table["ask"] = &term::ask;
        console_table["get_ansi"] = &term::get_ansi;
        // from c++ util::...
        util_table["system_launch"] = &util::launch;
        // From c++ math::
        math_table["abs"] = &math::abs<double>;
        math_table["lerp"] = &math::lerp<double>;
        math_table["clamp"] = &math::clamp<double>;
        math_table["approach"] = &math::approach<double>;
        math_table["remap"] = &math::remap<double>;
        // Lua console module
        console_table["pro_print"] = &lua::console::pro_print;
    }
}
