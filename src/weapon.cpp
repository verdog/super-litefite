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

Weapon::Weapon(shoe::GameState *state, shoe::GameObject &owner)
: shoe::GameObject(state) 
{
    mHurtPolygons.emplace_back(new HurtPolygon(owner, 2));

    std::shared_ptr<HurtPolygon> defaultPoly = mHurtPolygons.back();

    if (DebugState *s = dynamic_cast<DebugState*>(mState); s) {
        s->hurtPolygons.push_back(defaultPoly);
    }
}

void Weapon::setPosition(sf::Vector2f position) {
    shoe::GameObject::setPosition(position);
    for (std::shared_ptr<HurtPolygon> h : mHurtPolygons) {
        h->setPosition(position);
    }
}

void Weapon::setRotation(float rotation) {
    shoe::GameObject::setRotation(rotation);
    for (std::shared_ptr<HurtPolygon> h : mHurtPolygons) {
        h->setRotation(rotation);
    }
}

void Weapon::activate() {
    for (std::shared_ptr<HurtPolygon> h : mHurtPolygons) {
        h->toggle();
    }
}

void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (std::shared_ptr<HurtPolygon> h : mHurtPolygons) {
        target.draw(*h, states);
    }
}