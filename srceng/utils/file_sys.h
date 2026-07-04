#pragma once
#include <string>
#include <string_view>

namespace util{
    [[nodiscard]] std::string path(std::initializer_list<std::string_view> args) noexcept;
}
