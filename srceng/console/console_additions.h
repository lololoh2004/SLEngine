#pragma once
#include <span>
#include <string_view>
#include <string>


namespace term{
    void progress_bar(double current, double total);
    [[nodiscard]] size_t pick(std::string_view title, const std::span<const std::string> options);
}
