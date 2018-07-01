/*
 * player
 * 
 * Josh Chandler
*/

#pragma once

#include "../shoehorn/include/gameobject.hpp"

namespace shoe {
    class GameState;
}

class Player : public shoe::GameObject {
public:
    Player(shoe::GameState *state);
    ~Player();

    void handleInput(const sf::Time &dTime);
    void update(const sf::Time &dTime);

private:
};