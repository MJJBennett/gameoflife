#include "funcs.h"

std::string split_reverse(std::string str, char delim) {
    std::string ending = "";
    for (auto r_it = str.rbegin(); r_it != str.rend(); r_it++) {
        if (*r_it == delim) {
            return std::string(r_it.base(), str.end());
        } 
    }
    return str;
}