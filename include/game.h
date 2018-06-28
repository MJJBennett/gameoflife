#ifndef GAME_H
#define GAME_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "debug.h"
#include "Resource.h"
#include "tile.h"

class game {
public:
    game() : is_init(false), square_size(5) {}
    void init();
    void run();
private:
    sf::RenderWindow w;
    sf::RectangleShape our_rect;
    std::vector<std::vector<bool>> state;
    bool is_init;
    std::function<void(std::string)> write;
    int square_size;
    void set_square_size(int s);
    void draw_rect(int, int);
};

#endif //GAME_H