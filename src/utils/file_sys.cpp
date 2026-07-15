#include "file_sys.h"
#include <cstdlib>
#include <vector>
#include <filesystem>
#include "console/console_wrapper.hpp"

namespace util{
    [[nodiscard]] std::string path(std::initializer_list<std::string_view> args) noexcept {
        std::string result = "";
        for (auto i = args.begin(); i != args.end(); ++i){
            //std::string prefix = i == args.begin() ? "" : "/";
            std::string prefix = (result.empty() || result.back() == '/' || i->front() == '/') ? "" : "/";
            result.append(prefix).append(*i);
        }
        return result;
    }
    void launch(const std::string& file_path, const std::string& file_args) {
        if (file_path.empty()) return;
        std::string command = "start \"\" \"" + file_path + "\"";
        if (!file_args.empty()) {
            command += " " + file_args;
        }
        std::system(command.c_str());
    }
    [[nodiscard]] std::vector<std::string> directory_to_vector(const char* path,scan_modes mode){
        std::vector<std::string> result;
        std::error_code ec;

        for (const auto& object : std::filesystem::directory_iterator(path, ec)){
            switch (mode){
                case scan_modes::only_files:
                     if (object.is_regular_file())
                         result.push_back(object.path().string());
                    break;
                case scan_modes::only_folders:
                    if (object.is_directory())
                        result.push_back(object.path().string());
                    break;
                case scan_modes::all:
                    result.push_back(object.path().string());
                    break;
                default: break;
            }
        }
        if (ec){
            term::msg(ec.message());
        }
        return result;
    }

}
