/*
 * lightsource.cpp
 * 
 * Given a list of walls, calculates a visibility mask.
 * 
 * Josh Chandler
*/

#include <vector>
#include <iostream>

#include "shoehorn/include/gameobject.hpp"

#include "include/lightsource.hpp"

LightSource::LightSource(shoe::GameState *state, shoe::GameObject *anchor) 
: GameObject (state)
, mAnchor {anchor}
, mShape (sf::PrimitiveType::Quads)
, mColor {sf::Color::Black}
{
    
}

sf::VertexArray& LightSource::makeVisibilityShape(const std::vector<shoe::GameObject*>& obstacles) {
    mShape.clear();

    

}

void LightSource::update(const sf::Time &dTime) {
    setPosition(mAnchor->getPosition());
}

void LightSource::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape c;
    c.setOrigin(sf::Vector2f(4, 4));
    c.setPosition(getPosition());
    c.setPointCount(5);
    c.setRadius(4);
    target.draw(c);
}