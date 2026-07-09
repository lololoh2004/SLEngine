#pragma once
#include <filesystem>
#include <sol/sol.hpp>
#include <string_view>
#include "console/console_wrapper.hpp"

namespace lua{
    inline sol::state server_state;
    inline sol::state client_state; // --PLASEHOLDER--
    enum class states{
        server,client
    };

    inline void init_state(){
        server_state.open_libraries(sol::lib::base,
            sol::lib::package,sol::lib::string,
            sol::lib::table,sol::lib::math,
            sol::lib::ffi);
        server_state["ENGINE_PATH"] = std::filesystem::current_path().string();

        client_state.open_libraries(sol::lib::base);
    }

    [[nodiscard]] inline sol::state& get_state(states type) noexcept {
        switch (type){
        case states::server: return server_state;
        case states::client: return client_state;
        }
        return client_state;
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

    [[nodiscard]] inline std::unordered_map<std::string, std::string> table_to_hash (sol::table table) {
        std::unordered_map<std::string, std::string> result;

        for (auto [key, value] : table) {
            if (key.is<std::string>() && value.is<std::string>()) {
                std::string name = key.as<std::string>();
                std::string code = value.as<std::string>();

                result[name] = code;
            }
        }
        return result;
    }
}