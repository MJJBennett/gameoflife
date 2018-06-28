#include "Resource.h"

const std::string ResourceManager::RESOURCE_LOCATION = "../resources/";

resource * ResourceManager::retrieve_resource(const std::string& ID) {
    for (auto&& r : resources) if (r.ID == ID) return r.res.get();
    return load_resource(ID, false);
}

resource * ResourceManager::load_resource(std::string path, bool exclusive) {
    //All paths are relative to RESOURCE_LOCATION

    if (path == "") return nullptr;

    if (path.substr(0, 4)  == "RECT") {
        write("Loading a rect.");
        sf::RectangleShape r;
        if (exclusive) path+=std::to_string(resources.size()); //This is really bad, don't do this
        resources.push_back(ResourceWrapper{path, std::make_unique<resource>(r)});
        return resources.back().res.get();
    }

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

resource * ResourceManager::preload_resource(std::string path, bool exclusive) {
    return load_resource(std::move(path), exclusive);
}