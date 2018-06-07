/*
 * Josh Chandler
*/

#include <map>
#include <iostream>

#include "include/imagemanager.hpp"

namespace shoe {

ImageManager::ImageManager() {

}

ImageManager::~ImageManager() {
    // destroy all stored images?
}

bool ImageManager::loadImage(std::string key, std::string file) {
    sf::Texture tex;
    if (!tex.loadFromFile(file)) {
        return false;
    }

    mTextureMap.insert(std::pair<std::string, sf::Texture>(key, tex));

    return true;
}

sf::Texture* ImageManager::getImage(std::string key) {
    try {
        return &mTextureMap.at(key);
    } catch (...) {
        std::cerr << "ERROR: Could not retrieve image " << key << std::endl;
        return nullptr;
    }
}

}