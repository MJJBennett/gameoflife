#include "debug.h"
#include <iostream>
#define DO_DEBUG true

//To get a logger, call
//logger x = debug::get_debugger("source name")
std::function<void(std::string)> debug::get_debugger(std::string caller) {
#if DO_DEBUG == true
    return std::bind(&debug::_write_debug, std::placeholders::_1, caller);
#else
    return [](std::string) {};
#endif
}

void debug::_write_debug(std::string message, std::string caller) {
    std::cout << message << " (" << caller << ')' << std::endl;
}

void debug::err(const logger& write, std::string str) {
    std::cout << "ERROR OCCURRED: \n\t" << str;
    write("");
    std::cout << std::endl;
}

void debug::warn(const logger& write, std::string str) {
    std::cout << "Warning: \n\t";
    write("");
    std::cout << std::endl;
}

void debug::write_break(int i) {
#if DO_DEBUG
    std::cout << "Successfully executed up until break " << i << '.' << std::endl;
#endif
}