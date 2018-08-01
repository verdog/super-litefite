/*
 * sword
 * SUPER SHARP
 * 
 * Josh Chandler
*/

#include <memory>

#include <SFML/Graphics.hpp>

#include "include/sword.hpp"
#include "include/weapon.hpp"
#include "include/hurtpolygon.hpp"
#include "states/include/debugstate.hpp"

Sword::Sword(shoe::GameState *state, int length) 
: Weapon(state)
{
    mHurtPolygons.clear();
    sf::VertexArray load;
    load.resize(5);
    load[0] = sf::Vector2f(20, -4);
    load[1] = sf::Vector2f(20 + length, -4);
    load[2] = sf::Vector2f(20 + length + 2, 0);
    load[3] = sf::Vector2f(20 + length, 4);
    load[4] = sf::Vector2f(20, 4);
    std::shared_ptr<HurtPolygon> h(new HurtPolygon);
    h->loadPointsFromVertexArray(load);

    mHurtPolygons.push_back(h);

    setSpriteTexture(*mState->getTexture("sword"), true);
    setOrigin(sf::Vector2f(16, 30));

    setOrigin(sf::Vector2f(16, 48));
    rotate(90);
    move(sf::Vector2f(16, 16));
}

void Sword::update(const sf::Time &dTime) {
    Weapon::update(dTime);
}

void Sword::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform.combine(getTransform());
    target.draw(mSprite, states);
    Weapon::draw(target, states); // draw wireframe
}