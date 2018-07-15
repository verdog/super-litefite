/*
 * lightmask.cpp
 * 
 * A class to help with the combination of multiple light sources
 * 
 * Josh Chandler
*/

#include <vector>
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "include/lightsource.hpp"
#include "include/lightmask.hpp"

LightMask::LightMask(uint sizeX, uint sizeY) 
: mMask(new sf::RenderTexture)
, mBuffer(new sf::RenderTexture)
{
    mMask->create(sizeX, sizeY);
    mBuffer->create(sizeX, sizeY);
}

LightMask::~LightMask() {
    //
}

void LightMask::reset(sf::Color color) {
    mMask->clear(color);
}

void LightMask::add(const LightSource &light) {
    mBuffer->clear(light.getColor());
    mBuffer->draw(light.getVisibilityShape());
    mBuffer->display();
    mMask->draw(sf::Sprite(mBuffer->getTexture()), sf::RenderStates(sf::BlendAdd));
}

sf::Sprite& LightMask::sprite() {
    mMask->display();
    mSprite.setTexture(mMask->getTexture());
    return mSprite;
}