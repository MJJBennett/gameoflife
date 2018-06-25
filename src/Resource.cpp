#include "Resource.h"

const std::string ResourceManager::RESOURCE_LOCATION = "../resources/";

resource * ResourceManager::get_resource(grayscale g) {
    //Attempt to find the key in our mockery of a map
    for (auto&& r : resources) {
        if (r.ID == lookup) return r.res.get();
    }
    //Attempt to load the key (may return nullptr, might want to make this throw later)
    return load_resource(lookup);
}

resource * ResourceManager::get_resource(int typeID) {
    //Attempt to find the key in our mockery of a map
    for (auto&& r : resources) {
        if (r.ID == lookup) return r.res.get();
    }
    //Attempt to load the key (may return nullptr, might want to make this throw later)
    return load_resource(lookup);
}

resource * ResourceManager::load_resource(std::string path) {
    //All paths are relative to RESOURCE_LOCATION
    //Deduce resource type
    auto ext = split_reverse(path, '.');
}
