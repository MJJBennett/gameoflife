#include <algorithm>
#include <funcs.h>

#include "funcs.h"

std::string split_reverse(std::string str, char delim) {
    for (auto r_it = str.rbegin(); r_it != str.rend(); r_it++) {
        if (*r_it == delim) return std::string(r_it.base(), str.end());
    }
    return str; //Do not std::move this; it should be elided
}

/* So far as I can tell, these two string split implementations are essentially identical in runtime.
 * Ideally this could be tested further at a later date (or confirmed via Godbolt or something similar)
 * The second one is much nicer, though, so it will probably be used. It does require an additional library, however.
 * Now that I think about it, the split_reverse above could probably do the same thing...
 */

std::string _split_impl_1(std::string str, char delim) {
    for (auto it = str.begin(); it != str.end(); it++) {
        if (*it == delim) return std::string(str.begin(), it);
    }
    return str;
}

std::string _split_impl_2(std::string str, char delim) {
    return std::string(str.begin(), std::find(str.begin(), str.end(), delim));
}

std::string split(std::string str, char delim) {
    return _split_impl_2(std::move(str), delim);
}

void str_strip(std::string &str, char delim) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [delim](int c) {return c != delim;}));
    str.erase(std::find_if(str.rbegin(), str.rend(), [delim](int c) {return c != delim;}).base(), str.end());
}
