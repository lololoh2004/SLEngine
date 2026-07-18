#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace utils{
    enum class scan_modes{
        all, only_files, only_folders
    };
    [[nodiscard]] std::string path(std::initializer_list<std::string_view> args) noexcept;
    void launch(const std::string& file_path, const std::string& file_args);
    [[nodiscard]] std::vector<std::string> dir_to_vector(const char* dir_path);
    [[nodiscard]] std::string cur_dir();
}
