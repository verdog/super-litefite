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
    load[0] = sf::Vector2f(-16, -16);
    load[1] = sf::Vector2f(16, -16);
    load[2] = sf::Vector2f(16 + length, 0);
    load[3] = sf::Vector2f(16, 16);
    load[4] = sf::Vector2f(-16, 16);
    std::shared_ptr<HurtPolygon> h(new HurtPolygon);
    h->loadPointsFromVertexArray(load);

    mHurtPolygons.push_back(h);
}