#include "text.h"
#include <string>

namespace utils{
    void to_lower(std::string& str){
        for (char& c : str){
            if (c >= 'A' && c <= 'Z'){
                c += 32;
            }
        }
    }
}
