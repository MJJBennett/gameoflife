#ifndef DEBUG_H
#define DEBUG_H

#include <functional>
#include <iostream>

class debug {
public:
    static void write_break(int);
    static std::function<void(std::string)> get_debugger(std::string);
private:
    static void _write_debug(std::string, std::string);
};

#endif //DEBUG_H