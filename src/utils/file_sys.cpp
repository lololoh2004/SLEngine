#include "file_sys.h"

#include <vector>
#include "tinydir.h"
//#include <cstring>

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
    [[nodiscard]] std::vector<std::string> dir_to_vector(const char* dir_path){
        tinydir_dir dir;
        if (tinydir_open(&dir, dir_path) == 0){
            std::vector<std::string> result;
            while (dir.has_next){
                tinydir_file file;
                tinydir_readfile(&dir, &file);
                const char* file_name = file.name;
                if (file_name[0] == '.'){
                    if (file_name[1] == '\0' || file_name[1] == '.'){
                        tinydir_next(&dir);
                        continue;
                    }
                }
                result.push_back(file.name);
                tinydir_next(&dir);
            }
            tinydir_close (&dir);
            return result;
        }
        return {};
    }
    [[nodiscard]] std::string cur_dir() {
        tinydir_dir dir;
        if (tinydir_open(&dir, ".") == 0) {
            if (dir.has_next) {
                tinydir_file file;
                if (tinydir_readfile(&dir, &file) == 0) {
                    std::string full_path = file.path;
                    tinydir_close(&dir);

                    size_t last_slash = full_path.find_last_of("\\/");
                    if (last_slash != std::string::npos) {
                        return full_path.substr(0, last_slash);
                    }
                    return full_path;
                }
            }
            tinydir_close(&dir);
        }
        return "";
    }

}
