/*
 * lightsource.cpp
 * 
 * Given a list of walls, calculates a visibility mask.
 * 
 * Josh Chandler
*/

#include <vector>
#include <iostream>
#include <cmath>

#include "shoehorn/include/gameobject.hpp"
#include "shoehorn/include/collisionpolygon.hpp"
#include "shoehorn/include/vector2math.hpp"
#include "shoehorn/include/game.hpp"
#include "shoehorn/include/gamestate.hpp"

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
    sf::Vector2u gameSize = mState->getGame()->gameSize();
    float stretch = std::max(gameSize.x, gameSize.y) * 2;

    for (shoe::GameObject *o : obstacles) {
        shoe::CollisionPolygon c = o->collisionPolygon();

        for (uint i=0; i<c.getVertexCount(); i++) {
            sf::Vector2f begin = c.getTransform().transformPoint(c[i].position);
            sf::Vector2f end = c.getTransform().transformPoint(c[i+1 >= c.getVertexCount() ? 0 : i+1].position);
            sf::Vector2f beginRay = begin + stretch * (shoe::Vector2Math::normalize(begin - getPosition()));
            sf::Vector2f endRay = end + stretch * (shoe::Vector2Math::normalize(end - getPosition()));

            mShape.append(sf::Vertex(begin));
            mShape.append(sf::Vertex(end));
            mShape.append(sf::Vertex(endRay));
            mShape.append(sf::Vertex(beginRay));
        }
    }

    for (uint i=0; i<mShape.getVertexCount(); i++) {
        mShape[i].color = mColor;
    }
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

    target.draw(mShape);
}