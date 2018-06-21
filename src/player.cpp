/*
 * Player
 * 
 * Josh Chandler
*/

#include <SFML/Main.hpp>

#include "include/player.hpp"

Player::Player() {

}

Player::~Player() {

}

void Player::handleInput(const sf::Time &dTime) {
    bool input = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        mVelocity += sf::Vector2f(-5, 0);
        input = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        mVelocity += sf::Vector2f(5, 0);
        input = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        mVelocity += sf::Vector2f(0, -5);
        input = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        mVelocity += sf::Vector2f(0, 5);
        input = true;
    }

    if (!input) {
        mVelocity *= 0.98f;
    }
}

void Player::update(const sf::Time &dTime) {
    float dTimeSeconds = dTime.asSeconds();
    move(dTimeSeconds * mVelocity);
}