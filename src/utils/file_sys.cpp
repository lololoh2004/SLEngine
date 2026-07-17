#include "file_sys.h"
#include "tinydir.h"

namespace utils{
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

}
