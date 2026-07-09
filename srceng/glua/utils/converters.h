#pragma once
#include <string>
#include <unordered_map>
#include "sol/table.hpp"

namespace lua{
    [[nodiscard]] std::unordered_map<std::string, std::string> table_to_hash (sol::table table);
}

