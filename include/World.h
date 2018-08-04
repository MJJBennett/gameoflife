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
    void init(ResourceManager * r, unsigned int width = 100, unsigned int height = 100);
    void set_square_size(float s);

    void invert(int, int);

    int get_square_size();

    bool update();

    void dump_debug();

    void draw_all();

    void draw_canvas(sf::RenderWindow & window);
    void redraw_needed() { _redraw_needed = true; }
    //We're going to make this iterable
    //Note: This would (normally) be an incredibly bad idea
    //However, as this is mostly just a pet project for fun, we're doing this anyways
    WorldIter begin() { return WorldIter(this, 0); }
    WorldIter end() { return WorldIter(this, (int)updated_tiles.size()); }

    void reset();

private:
    bool side(int x, int y, int s);
    void resolve_square(int x, int y); //TODO
    logger write;
    unsigned int coord(int x, int y) const;
    unsigned int world_width = 100;
    unsigned int world_height = 100;
    std::vector<unsigned char> state;
    std::vector<unsigned int> updated_tiles = {};
    int square_size = 5;
    const sf::RectangleShape& get_rect(int, int) const;
    const sf::RectangleShape& get_rect(int) const;
    mutable sf::RectangleShape our_rect;
    ResourceManager * res = nullptr;
    sf::Color bg_color = sf::Color::Black;

    bool _redraw_needed =  false;
    void load();
};



#endif //CONWAYLIFE_WORLD_H
