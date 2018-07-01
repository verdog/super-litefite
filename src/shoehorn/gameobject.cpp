/* gameobject.cpp
 * a game object is anything in a game that can change during gameplay
 * 
 * Josh Chandler
*/

#include <iostream>
#include <cmath>

#include "include/gameobject.hpp"
#include "include/collisionpolygon.hpp"

const double pi = std::acos(-1);

namespace shoe {

GameObject::GameObject(GameState *state) 
: mState {state}
, mCollisionPoly(new CollisionPolygon)
{
    //
}

GameObject::~GameObject() {
    //
}

void GameObject::handleInput(const sf::Time &dTime) {
    //
}

void GameObject::update(const sf::Time &dTime) {

}

CollisionPolygon GameObject::collisionPolygon() const {
    return *mCollisionPoly;
}

bool GameObject::collidesWith(const GameObject &other) const {
    return mCollisionPoly->collidesWith(other.collisionPolygon());
}

bool GameObject::collidesWith(const CollisionPolygon &other) const {
    return mCollisionPoly->collidesWith(other);
}

void GameObject::makeIntoRegularShape(uint sides, uint radius) {
    mCollisionPoly->clear();
    mCollisionPoly->resize(sides);
    mCollisionPoly->setPrimitiveType(sf::PrimitiveType::LineStrip);

    float angle = 0;
    float increment = 360.f/sides;

    for (uint i=0; i<mCollisionPoly->getVertexCount(); i++) {
        (*mCollisionPoly)[i].position = sf::Vector2f(
            radius * std::cos(angle*pi/180.f),
            radius * std::sin(angle*pi/180.f)
        );
        angle += increment;
    }
}

void GameObject::makeIntoRect(sf::Vector2f size) {
    mCollisionPoly->clear();
    mCollisionPoly->resize(4);
    mCollisionPoly->setPrimitiveType(sf::PrimitiveType::LineStrip);

    (*mCollisionPoly)[0] = sf::Vector2f(0, 0);
    (*mCollisionPoly)[1] = sf::Vector2f(size.x, 0);
    (*mCollisionPoly)[2] = sf::Vector2f(size.x, size.y);
    (*mCollisionPoly)[3] = sf::Vector2f(0, size.y);
}

}