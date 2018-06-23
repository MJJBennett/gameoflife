#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "debug.h"

class game {
public:
    game() : is_init(false) {}
    void init();
    void run();
private:
    std::vector<std::vector<bool>> state;
    bool is_init;
    std::function<void(std::string)> write;
};

#endif //GAME_H