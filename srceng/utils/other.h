#pragma once
#include <string>
#include <string_view>

namespace util{
    [[nodiscard]] std::string to_lower(std::string_view text) noexcept;
}
