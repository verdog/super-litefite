/*
 * player
 * 
 * Josh Chandler
*/

#pragma once

#include "../shoehorn/include/gameobject.hpp"

class Player : public shoe::GameObject {
public:
    Player();
    ~Player();

    void handleInput(const sf::Time &dTime);
    void update(const sf::Time &dTime);

private:
};