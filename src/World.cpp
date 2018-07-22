#include "World.h"

const sf::RectangleShape& WorldIter::operator*() {
    return _world.get_rect()
}

int World::coord(int x, int y) const {
    if (x > world_width || x < 0 || y > world_height || y < 0) {
        write("[ERROR] X and Y entered out of bounds!");
        return -1;
    }
    int _coord = (world_width * y) + x;
    return _coord;
}

void World::init(ResourceManager * r) {
    write = debug::get_debugger("World.h");

    res = r;

    state.resize((size_t)(world_height * world_width));
    std::fill(state.begin(), state.end(), false);

    auto rect_p = r->retrieve_resource("RECT_GAMECPP");
    if (!rect_p) write("Rect could not be created!");
    our_rect = std::get<sf::RectangleShape>(*(r->retrieve_resource("RECT_GAMECPP")));
    our_rect.setFillColor(sf::Color::Red);

    //Test code that is meant to set up a 'square' of tiles
    for (int x = 0; x < world_width; x++) state[coord(x, 0)] = true;
    for (int x = 0; x < world_width; x++) state[coord(x, world_height-1)] = true;
    for (int y = 0; y < world_height; y++) state[coord(0, y)] = true;
    for (int y = 0; y < world_height; y++) state[coord(world_width - 1, y)] = true;
}

void World::set_square_size(float s) {
    square_size = (int)s;
    our_rect.setSize({s, s});
}

void World::get_rect(int x, int y) {
    our_rect.setPosition(x*square_size, y*square_size);
    w.draw(our_rect);
}

int World::get_square_size() {
    return square_size;
}

void World::resolve_square(int x, int y) {
}