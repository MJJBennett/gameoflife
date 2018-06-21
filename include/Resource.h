#ifndef CONWAY_RES_H
#define CONWAY_RES_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include <variant>
#include "funcs.h"

using resource = std::variant<sf::Texture, sf::Font>;

class ResourceManager {
public:
    ResourceManager() {}
    resource * get_resource(std::string);
private:
    struct ResourceWrapper {
        std::string ID;
        std::unique_ptr<resource> res;
    };

    const static std::string RESOURCE_LOCATION;

    std::vector<ResourceWrapper> resources;

    resource * load_resource(std::string);
};

#endif //CONWAY_RES_H