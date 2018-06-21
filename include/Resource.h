#ifndef CONWAY_RES_H
#define CONWAY_RES_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include <variant>

class ResourceManager {
public:
    ResourceManager() {}
    using resource = std::variant<sf::Texture, sf::Font>;
private:
    std::vector<std::unique_ptr<resource>> resources;
};

#endif //CONWAY_RES_H