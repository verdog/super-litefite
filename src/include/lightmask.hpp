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

class LightSource;

class LightMask {
public:
    LightMask(uint sizeX, uint sizeY);
    ~LightMask();

    void reset(sf::Color color = sf::Color::Black);
    void add(const LightSource &light);
    std::shared_ptr<sf::Sprite> sprite();

private:
    std::shared_ptr<sf::Sprite> mSprite;
    std::shared_ptr<sf::RenderTexture> mMask;
    std::unique_ptr<sf::RenderTexture> mBuffer;
};