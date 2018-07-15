/*
 * player
 * 
 * Josh Chandler
*/

#pragma once

#include <iostream>

#include "../shoehorn/include/gameobject.hpp"

namespace shoe {
    class GameState;
}

class LightSource;

class Player : public shoe::GameObject {
public:
    Player(shoe::GameState *state);
    ~Player();

    void handleInput(const sf::Time &dTime);
    void update(const sf::Time &dTime);

    LightSource& getLightSource() { return *mLightSource; }

    // debug method.
    void toggleReverse() {
        if (mReverse) {
            mReverse = false;
        } else {
            mReverse = true;
        }
    }

private:
    bool mReverse;
    std::shared_ptr<LightSource> mLightSource;
};