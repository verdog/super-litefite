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

Sword::Sword(shoe::GameState *state, shoe::GameObject &owner, int length) 
: Weapon(state, owner)
{
    mHurtPolygons.clear();
    // sf::VertexArray load;
    // load.resize(4);
    // load[0] = sf::Vector2f(-16, -16);
    // load[1] = sf::Vector2f(16, -16);
    // load[2] = sf::Vector2f(16, 16);
    // load[3] = sf::Vector2f(-16, 16);
    std::shared_ptr<HurtPolygon> h(new HurtPolygon);
    // h->loadPointsFromVertexArray(load);

    h->makeIntoRegularShape(4, 16);
    mHurtPolygons.push_back(h);

    if (DebugState *s = dynamic_cast<DebugState*>(mState); s) {
        s->hurtPolygons.push_back(h);
    }
}