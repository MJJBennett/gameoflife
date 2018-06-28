#ifndef CONWAY_RES_H
#define CONWAY_RES_H

#include <memory>
#include <functional>
#include <variant>
#include <utility>
#include <SFML/Graphics.hpp>
#include "funcs.h"
#include "debug.h"

using resource = std::variant<sf::Texture, sf::Font, sf::RectangleShape>;

class ResourceManager {
public:
    ResourceManager() { write = debug::get_debugger("game.cpp"); }
    resource * retrieve_resource(const std::string&);
    resource * preload_resource(std::string, bool exclusive = false);
private:
    std::function<void(std::string)> write;
    struct ResourceWrapper {
        std::string ID;
        std::unique_ptr<resource> res;
    };

    const static std::string RESOURCE_LOCATION;

    std::vector<ResourceWrapper> resources;

    resource * load_resource(std::string, bool exclusive = false);
};

#endif //CONWAY_RES_H