#pragma once
#include <filesystem>
#include <sol/sol.hpp>
#include <string_view>
#include "console/console_wrapper.hpp"
#include "utils/file_sys.h"

namespace lua{
    inline sol::state main_state;
    struct CallbackEl{
        std::string id;
        sol::function func;
    };
    inline std::unordered_map<std::string, std::vector<CallbackEl>> callbacks;
    enum class states{
        main
    };

    inline void init_state(){
        main_state.open_libraries(sol::lib::base,
            sol::lib::package,sol::lib::string,
            sol::lib::table,sol::lib::math,
            sol::lib::ffi);
        main_state["ENGINE_PATH"] = utils::cur_dir();
    }

    [[nodiscard]] inline sol::state& get_state(states type) noexcept {
        switch (type){
        case states::main: return main_state;
        }
        return main_state;
    }

    template <typename T>
    [[nodiscard]] T do_file(const std::string& path, sol::state& state) {
        if (!std::filesystem::exists(path))
            return T{};
        try{
            auto result = state.script_file(path);
            int count = result.return_count();
            [[assume(count >= 0)]];
            return count > 0 ? result.get<T>() : T{};
        }catch (const std::exception& error){
            term::msg(error.what(), "\n");
        }
        return T{};
    }
    inline void do_file(const std::string& path, sol::state& state){
        if (!std::filesystem::exists(path))
            return;
        try{
            state.script_file(path);
        } catch (const std::exception& error){
            term::msg(error.what(), "\n");
        }
    }

    template <typename Func>
    void add_func(std::string_view name, Func&& func, sol::state& state){
        state.set_function(name, std::forward<Func>(func));
    }

    // inline void call_func(sol::function& func, sol::state& state){
    //     func.call<void>();
    // }
    inline void add_callback(std::string_view name, std::string_view id, const sol::function& func){
        callbacks[std::string(name)].push_back({std::string(id), func});
    }
    inline void del_callback(std::string_view name, std::string_view id){
        std::erase_if(callbacks[std::string(name)], [&](const CallbackEl& el) {
            return el.id == id;
        });
    }
    inline void call_callback(std::string_view name){
        auto& callback_vec = callbacks[std::string(name)];
        for (auto& callback : callback_vec) {
            if (callback.func.valid()) {
                auto result = callback.func();
                if (!result.valid()) {
                    sol::error err = result;
                    term::msg("\n[LUA ERROR] : ");
                    term::msg(err.what());
                    term::msg("\n");
                }
            }
        }
    }
}
