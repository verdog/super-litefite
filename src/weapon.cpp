/*
 * weapon
 * stabby stab
 * 
 * Josh Chandler
*/

#include "shoehorn/include/gamestate.hpp"

#include "include/weapon.hpp"
#include "include/hurtpolygon.hpp"
#include "states/include/debugstate.hpp"

Weapon::Weapon(shoe::GameState *state)
: shoe::GameObject(state) 
{
    mHurtPolygons.emplace_back(new HurtPolygon(7));
}

void Weapon::setPosition(sf::Vector2f position) {
    for (std::shared_ptr<HurtPolygon> h : mHurtPolygons) {
        h->setPosition(position);
    }
}

void Weapon::setRotation(float rotation) {
    for (std::shared_ptr<HurtPolygon> h : mHurtPolygons) {
        h->setRotation(rotation);
    }
}

void Weapon::addVulnerability(const shoe::GameObject &object) {
    for (auto hp : mHurtPolygons) {
        hp->addVulnerability(object);
    }
}

void Weapon::removeVulnerability(const shoe::GameObject &object) {
    for (auto hp : mHurtPolygons) {
        hp->removeVulnerability(object);
    }
}

bool Weapon::canHurt(const shoe::GameObject &object) {
    for (auto hp : mHurtPolygons) {
        if (hp->canHurt(object)) {
            return true;
        }
    }
    return false;
}

void Weapon::activate() {
    for (std::shared_ptr<HurtPolygon> h : mHurtPolygons) {
        h->toggle();
    }
}

void Weapon::update(const sf::Time &dTime) {
    for (std::shared_ptr<HurtPolygon> hurtPolygon : mHurtPolygons) {
        for (shoe::GameObject go : hurtPolygon->getHurtList()) {
            if (canHurt(go) && hurtPolygon->collidesWith(go.getCollisionPolygon())) {
                std::cout << "did damage!\n";
            }
        }
    }
}

void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (std::shared_ptr<HurtPolygon> h : mHurtPolygons) {
        target.draw(*h, states);
    }
}