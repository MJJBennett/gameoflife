#ifndef CONWAYLIFE_WORLD_H
#define CONWAYLIFE_WORLD_H

#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Resource.h"
#include "debug.h"
#include <algorithm>

class World;

class WorldIter {
    //Note: Learned about the way to make custom iterators from
    //https://www.cprogramming.com/c++11/c++11-ranged-for-loop.html
public:
    WorldIter(const World * world, int pos) : _world(world), _pos(pos) {}

    bool operator!=(const WorldIter& other) {
        return _pos != other._pos;
    }

    const WorldIter& operator++() {
        ++_pos;
        return *this;
    }

    const sf::RectangleShape& operator*();
private:
    const World * _world;
    int _pos;
};

class World {
    friend WorldIter;
public:
    void init(ResourceManager * r);
    void set_square_size(float s);

    int get_square_size();

    bool update();

    void dump_debug();

    //We're going to make this iterable
    //Note: This would (normally) be an incredibly bad idea
    //However, as this is mostly just a pet project for fun, we're doing this anyways
    WorldIter begin() { return WorldIter(this, 0); }
    WorldIter end() { return WorldIter(this, (int)state.size()); }

    //testing only
    //const sf::RectangleShape& _get_rect(int, int) const;
private:
    bool side(int x, int y, int s);
    void resolve_square(int x, int y); //TODO
    std::function<void(std::string)> write;
    int coord(int x, int y) const;
    int world_width = 100;
    int world_height = 100;
    std::vector<unsigned char> state;
    int square_size = 5;
    const sf::RectangleShape& get_rect(int, int) const;
    const sf::RectangleShape& get_rect(int) const;
    mutable sf::RectangleShape our_rect;
    ResourceManager * res = nullptr;
    sf::Color bg_color = sf::Color::Black;
};



#endif //CONWAYLIFE_WORLD_H
