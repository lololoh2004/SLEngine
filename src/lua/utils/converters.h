#pragma once
#include <string>
#include <unordered_map>
#include "sol/table.hpp"

namespace lua{
    [[nodiscard]] std::unordered_map<std::string, std::string> table_to_hash (sol::table table);
    [[nodiscard]] sol::table strvec_to_tab(sol::state_view state, std::vector<std::string> vec);
}

