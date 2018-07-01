/*
 * Player
 * 
 * Josh Chandler
*/

#include <cmath>
#include <iostream>

#include <SFML/Main.hpp>

#include "../src/shoehorn/include/gamestate.hpp"
#include "../src/shoehorn/include/collisionpolygon.hpp"
#include "../src/shoehorn/include/fpscounter.hpp"

#include "states/include/debugstate.hpp"
#include "include/player.hpp"
#include "include/wallygon.hpp"

Player::Player(shoe::GameState *state) 
: GameObject(state)
{
    // setOrigin(16.f, 16.f);
    makeIntoRegularShape(6, 16);
    // makeIntoRect(sf::Vector2f(32.f, 32.f));
}

Player::~Player() {

}

void Player::handleInput(const sf::Time &dTime) {
    bool input = false;
    float delta = 2;
    float friction = 0.9;
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
        mVelocity *= friction;
    }
}

void Player::update(const sf::Time &dTime) {
    float dTimeSeconds = dTime.asSeconds();
    move(dTimeSeconds * mVelocity);
    // setRotation(std::atan2(mVelocity.y, mVelocity.x)*180/M_PIl);

    mCollisionPoly->setPosition(getPosition());

    if (dynamic_cast<DebugState*>(mState) != nullptr) {
        DebugState *state = dynamic_cast<DebugState*>(mState);

        for (Wallygon *w : state->mWalls) {
            if (w->collidesWith(*this)) {
                std::cout << "Player::update(): hit! " << state->mFPS->mFrames_total << "\n";
            }
        }
    } else {
        std::cerr << "ERROR: Error casting debugstate\n";
    }
}