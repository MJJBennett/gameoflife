#include "World.h"
#include <cmath> //For floor()
#include <iostream> //For debug

const sf::RectangleShape& WorldIter::operator*() {
    return _world->get_rect(_pos);
}

int World::coord(int x, int y) const {
    if (x > world_width || x < 0 || y > world_height || y < 0) {
        debug::err(write, "X and Y entered out of bounds!");
        return -1;
    }
    int _coord = (world_width * y) + x;
    return _coord;
}

void World::init(ResourceManager * r) {
    write = debug::get_debugger("World.h");

    res = r;

    state.resize((size_t)(world_height * world_width));

    auto rect_p = r->retrieve_resource("RECT_GAMECPP");
    if (!rect_p) debug::err(write, "Rect could not be created!");
    our_rect = std::get<sf::RectangleShape>(*(r->retrieve_resource("RECT_GAMECPP")));
    our_rect.setFillColor(sf::Color::Red);
    our_rect.setSize({(float)square_size, (float)square_size});

    reset();
}

void World::set_square_size(float s) {
    square_size = (int)s;
    our_rect.setSize({s, s});
}

const sf::RectangleShape& World::get_rect(int x, int y) const {
    our_rect.setPosition(x*square_size, y*square_size);
    return our_rect;
}

int World::get_square_size() {
    return square_size;
}

void World::resolve_square(int x, int y) {
}

const sf::RectangleShape& World::get_rect(int pos) const {
    if (state[pos] & 1) {
        our_rect.setFillColor(sf::Color::Green);
        //write("Returning a GREEN RECT");
    }
    else {
        our_rect.setFillColor(bg_color);
        //write("Returning a BLACK RECT");
    }
    int x = pos % world_width;
    auto y = static_cast<int>(floor(pos / world_width));
    //std::cout << "x: " << x << "y: " << y << '\n';
    return get_rect(x, y);
}

bool World::side(int x, int y, int s) {
    const bool DEFAULT_VALUE = false;
    switch (s) {
        case 0: //NW
            if (x == 0 || y == 0) return DEFAULT_VALUE;
            return (state[coord(x - 1, y - 1)] & 1) != 0;
        case 1: //N
            if (y == 0) return DEFAULT_VALUE;
            return (state[coord(x, y - 1)] & 1) != 0;
        case 2: //NE
            if (x == world_width-1 || y == 0) return DEFAULT_VALUE;
            return (state[coord(x + 1, y - 1)] & 1) != 0;
        case 3: //E
            if (x == world_width-1) return DEFAULT_VALUE;
            return (state[coord(x + 1, y)] & 1) != 0;
        case 4: //SE
            if (x == world_width-1 || y == world_height - 1) return DEFAULT_VALUE;
            return (state[coord(x + 1, y + 1)] & 1) != 0;
        case 5: //S
            if (y == world_height - 1) return DEFAULT_VALUE;
            return (state[coord(x, y + 1)] & 1) != 0;
        case 6: //SW
            if (x == 0 || y == world_height-1) return DEFAULT_VALUE;
            return (state[coord(x - 1, y + 1)] & 1) != 0;
        case 7: //W
            if (x == 0) return DEFAULT_VALUE;
            return (state[coord(x - 1, y)] & 1) != 0;
        default:
            write("[ERROR] Incompatible side found! SIDE#" + std::to_string(s));
            return false;
    }
}

bool World::update() {
    for (int x = 0; x < world_width; x++) {
        for (int y = 0; y < world_height; y++) {
            int count = 0;
            for (int s = 0; s < 8; s++) {
                //each direction of 8, N/NE/E/etc
                if (side(x,y,s)) count++;
                if (count > 3) break;
            }
            if ((int)(state[coord(x,y)] & 1) == 0) {
                //The cell is currently dead
                //std::cout << "Dead cell @ " << x << ',' << y << '\n';
                if (count == 3) {
                    //Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
                    state[coord(x,y)] = 2;
                }
                continue;
            }
            //write("Doing live cell. Count: " + std::to_string(count));
            switch(count) {
                //Any live cell with fewer than two live neighbors dies, as if by under population.
                case 0:
                case 1:
                    state[coord(x, y)] = static_cast<unsigned char>(state[coord(x, y)] & 1);
                    break;
                //Any live cell with two or three live neighbors lives on to the next generation.
                case 2:
                case 3:
                    state[coord(x, y)] = static_cast<unsigned char>(state[coord(x, y)] | (1 << 1));
                    break;
                //Any live cell with more than three live neighbors dies, as if by overpopulation.
                case 4:
                    state[coord(x, y)] = static_cast<unsigned char>(state[coord(x, y)] & 1);
                    break;
                default:
                    write("[ERROR] Count of " + std::to_string(count) + " was registered!");
            }
        }
    }
    for (unsigned char &i : state) i = i >> 1;
}

void World::dump_debug() {
    write("Dumping world debug.");
    write("World state:");
    for (int y = 0; y < world_width; y++) {
        std::cout << '|';
        for (int x = 0; x < world_height; x++) {
            std::cout << (int)state[coord(x, y)] << '|';
        }
        std::cout << std::endl;
    }
}

void World::reset() {
    std::fill(state.begin(), state.end(), 0);
    load();
}

void World::load() {
    //Test code that is meant to set up a 'square' of tiles
    for (int x = 0; x < world_width; x++) state[coord(x, 0)] = 1;
    for (int x = 0; x < world_width; x++) state[coord(x, world_height-1)] = 1;
    for (int y = 0; y < world_height; y++) state[coord(0, y)] = 1;
    for (int y = 0; y < world_height; y++) state[coord(world_width - 1, y)] = 1;
    state[0] = 1;
    state[1] = 1;
    state[coord(0, 1)] = 1;
    state[coord(1, 1)] = 1;

//    state[coord(4, 10)] = 1;
//    state[coord(4, 11)] = 1;
//    state[coord(4, 13)] = 1;
//    state[coord(4, 14)] = 1;
//
//    state[coord(5, 10)] = 1;
//    state[coord(5, 14)] = 1;
//
//    state[coord(6, 11)] = 1;
//    state[coord(6, 12)] = 1;
//    state[coord(6, 13)] = 1;
//
//    state[coord(7, 12)] = 1;

//    state[coord(5, 5)] = 1;
//    state[coord(5, 6)] = 1;
//    state[coord(5, 7)] = 1;
}