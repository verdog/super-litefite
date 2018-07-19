/*
 * Player
 * 
 * Josh Chandler
*/

#include <cmath>
#include <iostream>
#include <memory>

#include <SFML/Main.hpp>

#include "../src/shoehorn/include/gamestate.hpp"
#include "../src/shoehorn/include/gameobject.hpp"
#include "../src/shoehorn/include/collisionpolygon.hpp"
#include "../src/shoehorn/include/fpscounter.hpp"
#include "../src/shoehorn/include/vector2math.hpp"

#include "states/include/debugstate.hpp"
#include "include/player.hpp"
#include "include/lightsource.hpp"
#include "include/wallygon.hpp"
#include "include/hurtpolygon.hpp"
#include "include/weapon.hpp"
#include "include/sword.hpp"

Player::Player(shoe::GameState *state) 
: GameObject(state)
, mAlive {true}
, mHP {100}
, mLightSource (new LightSource(state, *this))
, mWeapon (new Sword(mState, 10))
{
    std::cout << "Player()\n";

    setOrigin(16.f, 16.f);
    makeIntoRegularShape(7, 12);
    // makeIntoRect(sf::Vector2f(32.f, 32.f));

    mPhysics.friction = 0.95;
    mPhysics.bounce = 0.25;
    mPhysics.drag = 0.9;

    mReverse = false;
}

Player::~Player() {
    std::cout << "Player got deleted.\n";
}

void Player::handleInput(const sf::Time &dTime) {
    bool input = false;
    float delta = 6;
    if (mReverse) {
        delta *= -1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        mVelocity += sf::Vector2f(-delta, 0);
        input = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        mVelocity += sf::Vector2f(delta, 0);
        input = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        mVelocity += sf::Vector2f(0, -delta);
        input = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        mVelocity += sf::Vector2f(0, delta);
        input = true;
    }

    if (!input) {
        mVelocity *= mPhysics.drag;
    }
}

void Player::update(const sf::Time &dTime) {
    float dTimeSeconds = dTime.asSeconds();
    move(dTimeSeconds * mVelocity);
    setRotation(std::atan2(mVelocity.y, mVelocity.x)*180/M_PIl);

    mCollisionPolygon->setPosition(getPosition());
    mWeapon->setPosition(getPosition());
    mWeapon->setRotation(getRotation());
    mWeapon->update(dTime);

    if (dynamic_cast<DebugState*>(mState) != nullptr) {
        DebugState *state = dynamic_cast<DebugState*>(mState);

        for (std::shared_ptr<Wallygon> w : state->mWalls) {
            sf::Vector2f MTA = -w->collidesWith(*this);
            // we make this negative because collidesWith() returns how much the
            // caller of the function should move (so here, it returns how much the wall should move.)
            // we want to move the player, not the wall, so we invert it

            if (MTA != sf::Vector2f(0, 0)) {
                move(MTA);
                using sMath = shoe::Vector2Math;
                sf::Vector2f nVelocity = sMath::dot(mVelocity, MTA)/sMath::dot(MTA, MTA) * MTA;
                sf::Vector2f pVelocity = mVelocity - nVelocity;

                mVelocity = mPhysics.friction * pVelocity - mPhysics.bounce * nVelocity;
            }
        }

        std::vector<std::shared_ptr<shoe::GameObject>> tempWalls(state->mWalls.begin(), state->mWalls.end());
        mLightSource->update(dTime);
        mLightSource->makeVisibilityShape(tempWalls);
    } else {
        std::cerr << "ERROR: Error casting debugstate\n";
    }
}

LightSource& Player::getLightSource() { 
    return *mLightSource; 
}

Weapon& Player::getWeapon() {
    return *mWeapon;
}