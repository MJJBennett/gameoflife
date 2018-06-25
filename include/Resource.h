#ifndef CONWAY_RES_H
#define CONWAY_RES_H

#include <memory>
#include <functional>
#include <variant>
#include <utility>
#include <SFML/Graphics.hpp>
#include "funcs.h"

using resource = std::variant<sf::Texture, sf::Font>;

class grayscale {
public:
    grayscale(int i) explicit: data(i) {};
    grayscale& operator++() {data++; constrain();}
    grayscale& operator=(const int& i) {data = i; constrain();}
private:
    int data;
    void constrain() {if (data < 0) data = 0; if (data > 255) data = 255;}
};

class ResourceManager {
public:
    ResourceManager() {}
    template<typename T>
    resource * get_resource(grayscale);
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