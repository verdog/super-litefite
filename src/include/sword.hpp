/*
 * sword
 * SUPER SHARP
 * 
 * Josh Chandler
*/

#pragma once

#include "weapon.hpp"

class Sword : public Weapon {
public:
    Sword(shoe::GameState *state, int length);

    // void activate();
    void update(const sf::Time &dTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
};