/*
 * Josh Chandler
*/

#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace shoe {

class TextureManager {
public:
    TextureManager();
    ~TextureManager();

    bool loadTexture(std::string key, std::string file);
    sf::Texture* getTexture(std::string key);
private:
    std::map<std::string, sf::Texture> mTextureMap;
};

}