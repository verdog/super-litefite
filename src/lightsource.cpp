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

LightSource::LightSource(shoe::GameState *state, shoe::GameObject &anchor) 
: GameObject (state)
, mAnchor {anchor}
, mShape (sf::PrimitiveType::Quads)
, mColor {sf::Color::White}
, mOn { true }
{
    //
}

sf::VertexArray& LightSource::makeVisibilityShape(const std::vector<std::shared_ptr<GameObject>>& obstacles) {
    mShape.clear();

    if (mOn == false) {
        sf::Vector2f gameSize = sf::Vector2f(mState->getGame()->gameSize());
        // draw one big black rect if light is off
        mShape.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::Black));
        mShape.append(sf::Vertex(sf::Vector2f(0, gameSize.y), sf::Color::Black));
        mShape.append(sf::Vertex(sf::Vector2f(gameSize.x, gameSize.y), sf::Color::Black));
        mShape.append(sf::Vertex(sf::Vector2f(gameSize.x, 0), sf::Color::Black));
        return mShape;
    }

    sf::Vector2u gameSize = mState->getGame()->gameSize();
    float stretch = std::max(gameSize.x, gameSize.y) * 2;

    for (std::shared_ptr<shoe::GameObject> o : obstacles) {
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

    /*
     * this is all poc cone of visibility stuff
    */

    // sf::Vector2i mousei = sf::Mouse::getPosition(mState->getGame()->window());
    // sf::Vector2f mousef = sf::Vector2f(mousei.x, mousei.y) / (float)mState->getGame()->pixelScale();

    // sf::Vector2f lineOfSight = shoe::Vector2Math::normalize(mousef - getPosition());
    // sf::Vector2f normal = shoe::Vector2Math::normal(lineOfSight);
    // sf::Transform CCW;
    // sf::Transform CW;
    // sf::Transform CCWCorner;
    // sf::Transform CWCorner;
    // CCW.rotate(-1);
    // CW.rotate(1);
    // CCWCorner.rotate(-45);
    // CWCorner.rotate(45);

    // sf::Vector2f begin = getPosition();
    // sf::Vector2f CCWRay = begin + stretch * CCW.transformPoint(lineOfSight);
    // sf::Vector2f corner = begin + stretch * CCWCorner.transformPoint(lineOfSight);
    // sf::Vector2f longNormal = begin + stretch * normal;

    // mShape.append(sf::Vertex(begin));
    // mShape.append(sf::Vertex(CCWRay));
    // mShape.append(sf::Vertex(corner));
    // mShape.append(sf::Vertex(longNormal));

    // sf::Vector2f CWRay = begin + stretch * CW.transformPoint(lineOfSight);
    // sf::Vector2f corner2 = begin + stretch * CWCorner.transformPoint(lineOfSight);
    // sf::Vector2f longNormal2 = begin + stretch * -normal;

    // mShape.append(sf::Vertex(begin));
    // mShape.append(sf::Vertex(CWRay));
    // mShape.append(sf::Vertex(corner2));
    // mShape.append(sf::Vertex(longNormal2));

    // sf::Vector2f backCorner1 = begin - stretch * CW.transformPoint(lineOfSight);
    // sf::Vector2f backCorner2 = begin - stretch * CCW.transformPoint(lineOfSight);

    // mShape.append(sf::Vertex(longNormal));
    // mShape.append(sf::Vertex(backCorner1));
    // mShape.append(sf::Vertex(backCorner2));
    // mShape.append(sf::Vertex(longNormal2));

    for (uint i=0; i<mShape.getVertexCount(); i++) {
        mShape[i].color = sf::Color::Black;
    }

    return mShape;
}

sf::VertexArray LightSource::getVisibilityShape() const {
    return mShape;
}

void LightSource::update(const sf::Time &dTime) {
    setPosition(mAnchor.getPosition());
}

void LightSource::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape c;
    c.setOrigin(sf::Vector2f(4, 4));
    c.setPosition(getPosition());
    c.setPointCount(5);
    c.setRadius(4);
    target.draw(c);

    // target.draw(mShape);
}

bool LightSource::isOn() {
    return mOn;
}

void LightSource::turnOn() {
    mOn = true;
}

void LightSource::turnOff() {
    mOn = false;
}

bool LightSource::toggle() {
    if (mOn) {
        mOn = false;
    } else {
        mOn = true;
    }

    return mOn;
}