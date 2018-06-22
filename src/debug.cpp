#include "debug.h"

std::function<void(std::string)> debug::get_debugger(std::string caller) {
    return std::bind(&debug::_write_debug, std::placeholders::_1, caller);
}

void debug::_write_debug(std::string message, std::string caller) {
    std::cout << message << " (" << caller << ')' << std::endl;
}