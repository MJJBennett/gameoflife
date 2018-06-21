#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class game {
public:
    void init();
private:
    std::vector<std::vector<bool>> state;
};

#endif //GAME_H