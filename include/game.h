#ifndef GAME_H
#define GAME_H

#include "debug.h"
#include <algorithm>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Resource.h"
#include <World.h>

class game {
public:
    void init();
    void run();
private:
    sf::RenderWindow w;
    bool is_init = false;
    logger write;
};

#endif //GAME_H