#include "init_lua_modules.h"

#include <sol/sol.hpp>

#include "lua_env.hpp"
#include "api/console.h"
#include "../utils/math_extension.hpp"
#include "utils/file_sys.h"
#include "console/console_wrapper.hpp"
#include "render/ui_el_logic.h"
#include "utils/converters.h"

namespace lua::base{
    void init_base_api(sol::state& state){
        // Table tree API structure
        sol::table engine_table  = state["engine"].get_or_create<sol::table>();
        sol::table math_table    = state["math"].get_or_create<sol::table>();
        sol::table util_table    = state["utils"].get_or_create<sol::table>();
        sol::table console_table = state["console"].get_or_create<sol::table>();
        sol::table sgui_table    = state["sgui"].get_or_create<sol::table>();
        //sol::table convert_table = state["convert"].get_or_create<sol::table>();
        // Functions
        // From c++ term::...
        console_table["clear"] = &term::clear;
        console_table["msg"] = [](const char* text) {
            term::msg(text);
        };
        console_table["get_ansi"] = &term::get_ansi;
        console_table["ask"] = &term::ask;
        // from c++ util::...
        util_table["system_launch"] = &utils::launch;
        //util_table["dir_to_vector"] = &utils::dir_to_vector;
        util_table["dir_to_tab"] = [](const char* path, sol::this_state state) -> sol::table{
            auto vec = utils::dir_to_vector(path);
            return lua::strvec_to_tab(state, vec);
        };
        util_table["path"] = &utils::path;
        // From c++ math::
        math_table["abs"] = &math::abs<double>;
        math_table["lerp"] = &math::lerp<double>;
        math_table["clamp"] = &math::clamp<double>;
        math_table["approach"] = &math::approach<double>;
        math_table["remap"] = &math::remap<double>;
        // Hook system from c++:
        engine_table["add_hook"] = &lua::add_callback;
        engine_table["del_hook"] = &lua::del_callback;
        engine_table["call_hook"] = &lua::call_callback;
        // Lua console module
        console_table["pro_print"] = &lua::lua_term::pro_print;
        console_table["pick"] = &lua::lua_term::lua_pick;
        // Lua sgui system module
        sgui_table["begin_window"] = &render::begin_window;
        sgui_table["add_text"] = &render::add_button;
        sgui_table["add_button"] = &render::add_button;
        sgui_table["end_window"]   = &render::end_window;
        // Converters:
    }
}
