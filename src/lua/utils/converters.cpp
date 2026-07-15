#include "converters.h"

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
}
