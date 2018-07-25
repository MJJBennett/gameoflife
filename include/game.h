#ifndef GAME_H
#define GAME_H

#include "debug.h"
#include <algorithm>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Resource.h"
#include <World.h>

struct KEY_COMBO {
    //Used to store information on key combos
    bool active = false;
    std::string str_state = "";
    int get_num() {
        return std::stoi(str_state);
    }
    void add_num(int in) {
        if (str_state.length() <= 6)
            str_state += std::to_string(in);
    }
    void reset() {
        str_state.clear();
        active = false;
    }
};

class game {
public:
    void init();
    void run();
private:
    sf::RenderWindow w;
    bool is_init = false;
    logger write;

    void handle_keyboard(sf::Keyboard::Key);

    World world;
    KEY_COMBO key_combo;
};

#endif //GAME_H