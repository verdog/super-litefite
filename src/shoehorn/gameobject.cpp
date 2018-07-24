/* gameobject.cpp
 * a game object is anything in a game that can change during gameplay
 * 
 * Josh Chandler
*/

#include <iostream>
#include <cmath>
#include <memory>

#include "include/gameobject.hpp"
#include "include/collisionpolygon.hpp"
#include "include/spriteanimator.hpp"

const double pi = std::acos(-1);

namespace shoe {

int GameObject::mNextId = 0;

GameObject::GameObject(GameState *state) 
: spriteAnimator (this)
, mState {state}
, mCollisionPolygon (new CollisionPolygon()) // shared_ptr
, mId ( mNextId++ )
{
    std::cout << "Created object with Id: " << mId << std::endl;
}

GameObject::~GameObject() {
    //
}

void GameObject::handleInput(const sf::Time &dTime) {
    //
}

void GameObject::update(const sf::Time &dTime) {

}

CollisionPolygon GameObject::getCollisionPolygon() const {
    return *mCollisionPolygon;
}

Collision GameObject::collidesWith(const GameObject &other) const {
    return mCollisionPolygon->collidesWith(other.getCollisionPolygon());
}

Collision GameObject::collidesWith(const CollisionPolygon &other) const {
    return mCollisionPolygon->collidesWith(other);
}

void GameObject::makeIntoRegularShape(uint sides, uint radius) {
    mCollisionPolygon->makeIntoRegularShape(sides, radius);
}

void GameObject::makeIntoRect(sf::Vector2f size) {
    mCollisionPolygon->clear();
    mCollisionPolygon->resize(4);
    mCollisionPolygon->setPrimitiveType(sf::PrimitiveType::LineStrip);

    (*mCollisionPolygon)[0] = sf::Vector2f(0, 0);
    (*mCollisionPolygon)[1] = sf::Vector2f(size.x, 0);
    (*mCollisionPolygon)[2] = sf::Vector2f(size.x, size.y);
    (*mCollisionPolygon)[3] = sf::Vector2f(0, size.y);
}

void GameObject::setSpriteTexture(const sf::Texture &texture, bool resetRect) {
    mSprite.setTexture(texture, resetRect);
}

void GameObject::setSpriteTextureRect(const sf::IntRect &rectangle) {
    mSprite.setTextureRect(rectangle);
}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform.combine(getTransform());
    target.draw(mSprite, states);
}

}