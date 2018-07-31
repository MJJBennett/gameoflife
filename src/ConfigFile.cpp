#include "ConfigFile.h"
#include "funcs.h"
#include <algorithm>
#include <iostream>
#include <ConfigFile.h>


void ConfigFile::parse() {
    configuration.clear();
    //Open configuration file
    auto f = std::ifstream(_filename);
    if (!f.good()) {
        debug::err(write, "Could not open configuration file for parsing!");
        return;
    }
    std::string str = "";
    int _line = 0;
    int _skipped = 0;
    char delim = '=';
    char comment = '#';
    while (std::getline(f, str)) {
        str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
        _line+=1;
        std::string expr = split(str, comment);
        auto pos = expr.find(delim);
        if (pos != std::string::npos && pos != 0) {
            if (_skipped) {
                write("Skipped " + std::to_string(_skipped) + " line(s)");
                _skipped=0;
            }
            std::string var(expr.begin(), std::find(expr.begin(), expr.end(), delim));
            std::string val(std::find(expr.begin(), expr.end(), delim)+1, expr.end());
            str_strip(var);
            str_strip(val);
            write("Var: " + var + "; val: " + val);
            configuration[var] = val;
        }
        else _skipped++;
    }
}

const std::basic_string<char> & ConfigFile::get(std::string var) const {
    if (configuration.find(var) == configuration.end()) return get_filename();
    return configuration.at(var);
}

const std::basic_string<char> & ConfigFile::at(std::string var) const {
    return get(std::move(var));
}

const std::string &ConfigFile::get_or_add_default(std::string var, std::string default_value) {
    if (at(var) == get_filename()) configuration[var] = default_value;
    return at(var);
}
