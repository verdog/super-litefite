/*
 * weapon
 * stabby stab
 * 
 * Josh Chandler
*/

#include "shoehorn/include/gamestate.hpp"

#include "include/weapon.hpp"
#include "include/hurtpolygon.hpp"
#include "include/hurtpolygon-animator.hpp"
#include "states/include/debugstate.hpp"

Weapon::Weapon(shoe::GameState *state)
: shoe::GameObject(state) 
, mHurtPolygons (new HurtPolygonAnimator)
{
    mHurtPolygons->insert(std::make_shared<HurtPolygon>(3));
}

void Weapon::setHurtPolygonPosition(sf::Vector2f position) {
    mHurtPolygons->setPosition(position);
}

void Weapon::rotateHurtPolygon(float angle) {
    mHurtPolygons->rotate(angle);
}

void Weapon::setHurtPolygonRotation(float rotation) {
    mHurtPolygons->setRotation(rotation);
}

void Weapon::addVulnerability(const shoe::GameObject &object) {
    mHurtPolygons->addVulnerability(object);
}

void Weapon::removeVulnerability(const shoe::GameObject &object) {
    mHurtPolygons->removeVulnerability(object);
}

bool Weapon::canHurt(const shoe::GameObject &object) {
    return mHurtPolygons->canHurt(object);
}

void Weapon::activate() {
    // mHurtPolygons->Play?
}

void Weapon::update(const sf::Time &dTime) {
    mHurtPolygons->update(dTime);
}

void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    mHurtPolygons->draw(target, states);
}
