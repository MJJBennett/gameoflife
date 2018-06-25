#pragma once

#include <Resource.h>
#include <SFML/System/Vector2.hpp>

struct tile {
    tile() {m_position = sf::Vector2i(0,0);}
    void draw(ResourceManager *, sf::RenderWindow&);
    sf::Vector2i m_position;
};