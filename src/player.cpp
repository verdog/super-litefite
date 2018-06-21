/*
 * Player
 * 
 * Josh Chandler
*/

#include <cmath>

#include <SFML/Main.hpp>

#include "include/player.hpp"

Player::Player() {
    setOrigin(16.f,16.f);
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
    setRotation(std::atan2(mVelocity.y, mVelocity.x)*180/M_PIl);
}