/*
 * Josh Chandler
*/

#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace shoe {

class ImageManager {
public:
    ImageManager();
    ~ImageManager();

    bool loadImage(std::string key, std::string file);
    sf::Texture* getImage(std::string key);
private:
    std::map<std::string, sf::Texture> mTextureMap;
};

}