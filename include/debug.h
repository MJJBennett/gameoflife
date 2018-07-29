#ifndef DEBUG_H
#define DEBUG_H

#include <functional>

using logger = std::function<void(std::string)>;

class debug {
public:
    static logger get_debugger(std::string);
    static void write_break(int);
    static void err(const logger&, std::string);
    static void warn(const logger&, std::string);
private:
    static void _write_debug(std::string, std::string);
};

#endif //DEBUG_H