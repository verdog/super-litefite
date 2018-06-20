/*
 * Josh Chandler
*/

#include <map>
#include <iostream>

#include "include/texturemanager.hpp"

namespace shoe {

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {
    // destroy all stored Textures?
}

bool TextureManager::loadTexture(std::string key, std::string file) {
    sf::Texture tex;
    if (!tex.loadFromFile(file)) {
        return false;
    }

    mTextureMap.insert(std::pair<std::string, sf::Texture>(key, tex));

    return true;
}

sf::Texture* TextureManager::getTexture(std::string key) {
    try {
        return &mTextureMap.at(key);
    } catch (...) {
        std::cerr << "ERROR: Could not retrieve Texture " << key << std::endl;
        return nullptr;
    }
}

}