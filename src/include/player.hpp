/*
 * player
 * 
 * Josh Chandler
*/

#pragma once

#include <iostream>

#include "../shoehorn/include/gameobject.hpp"
#include "../shoehorn/include/objectmanager.hpp"

namespace shoe {
    class GameState;
}

class LightSource;
class HurtPolygon;
class Weapon;

class Player : public shoe::GameObject {
public:
    Player(shoe::GameState *state);
    ~Player();

    void handleInput(const sf::Time &dTime);
    void update(const sf::Time &dTime);

    LightSource& getLightSource();
    Weapon& getWeapon();

    // debug function.
    void toggleReverse() {
        if (mReverse) {
            mReverse = false;
        } else {
            mReverse = true;
        }
    }

private:
    bool mReverse;
    bool mAlive;
    int mHP;
    std::shared_ptr<LightSource> mLightSource;
    std::shared_ptr<Weapon> mWeapon;
};