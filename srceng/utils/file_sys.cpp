#include "file_sys.h"

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
}
