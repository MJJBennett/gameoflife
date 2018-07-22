#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <memory>
#include <SFML/Graphics.hpp>
#include "debug.h"
#include "Resource.h"
#include "tile.h"
#include <World.h>

class game {
public:
    game() = default;
    void init();
    void run();
private:
    sf::RenderWindow w;
    bool is_init = false;
    std::function<void(std::string)> write;
};

#endif //GAME_H