#include "converters.h"

#include "sol/state.hpp"

namespace lua{
    [[nodiscard]] std::unordered_map<std::string, std::string> table_to_hash (sol::table table) {
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
    [[nodiscard]] sol::table strvec_to_tab(sol::state_view state, std::vector<std::string> vec){
        sol::table result = state.create_table();
        for (auto it = vec.begin(); it != vec.end(); ++it){
            size_t index = (it - vec.begin()) + 1;
            result[index] = *it;
        }
        return result;
    }
}
