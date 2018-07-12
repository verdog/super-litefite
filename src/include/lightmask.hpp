/*
 * lightmask.hpp
 * 
 * A class to help with the combination of multiple light sources
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

class LightMask {
public:
    LightMask();
    ~LightMask();

    void reset();
    void addToMask(const sf::RenderTexture &tex);
    std::shared_ptr<sf::RenderTexture> mask();

private:
    std::shared_ptr<sf::RenderTexture> mMask;
};