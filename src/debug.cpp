#include "debug.h"
#include <iostream>

std::function<void(std::string)> debug::get_debugger(std::string caller) {
    return std::bind(&debug::_write_debug, std::placeholders::_1, caller);
}

void debug::_write_debug(std::string message, std::string caller) {
    std::cout << message << " (" << caller << ')' << std::endl;
}

void debug::err(const logger& write, std::string str) {
    std::cout << "ERROR OCCURRED: \n\t";
    write(std::move(str));
}

void debug::write_break(int i) {
    std::cout << "Successfully executed up until break " << i << '.' << std::endl;
}