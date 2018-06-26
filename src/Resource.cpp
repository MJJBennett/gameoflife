#include "Resource.h"

const std::string ResourceManager::RESOURCE_LOCATION = "../resources/";

resource * ResourceManager::retrieve_resource(const std::string& ID) {
    for (auto&& r : resources) if (r.ID == ID) return r.res.get();
    return load_resource(ID);
}

resource * ResourceManager::load_resource(std::string path) {
    //All paths are relative to RESOURCE_LOCATION



    //Deduce resource type
    auto ext = split_reverse(path, '.');
    if (ext == "jpg" || ext == "jpeg" || ext == "png") {
        write("Loading a texture.");
        sf::Texture t;
        t.loadFromFile(RESOURCE_LOCATION + path);
        resources.push_back(ResourceWrapper{path, std::make_unique<resource>(t)});
        return resources.back().res.get();
    }
    return nullptr;
}

void ResourceManager::preload_resource(std::string path) {
    load_resource(std::move(path));
}