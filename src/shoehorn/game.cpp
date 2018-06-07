/* game.cpp
 * basic game class
 * 
 * Josh Chandler
*/

#include <iostream>

#include "include/game.hpp"

namespace shoe {

Game::Game(std::string title)
: mWindow (sf::VideoMode(256,256), "shoeGame")
, mStates()
, mInitialized {false}
, mRunning {false}
{
    setWindowTitle(title);
}

bool Game::init() {
    mInitialized = true;

    return true;
}

bool Game::run() {
    if (!mInitialized) {
        init();
    }

    mRunning = true;

    while (mRunning) {
        sf::Event e;
        while (mWindow.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    mRunning = false;
                    break;

                case sf::Event::KeyPressed:
                    if (e.key.code == sf::Keyboard::X) {
                        popState();
                    }
            
                default:
                    break;
            }   
        }

        if (!mStates.empty()) {
            mStates.back()->clear();
            mStates.back()->update();
            mStates.back()->display();
        } else {
            mRunning = false;
            std::cerr << "ERROR: No state on state stack!\n"; 
        }
    }

    return true;
}

// window management
sf::RenderWindow& Game::window() {
    return mWindow;
}

void Game::setWindowSize(uint x, uint y) {
    mWindow.setSize(sf::Vector2u(x, y));
}

void Game::setWindowTitle(std::string title) {
    mWindow.setTitle(title);
}

// state management
void Game::pushState(GameState *state) {
    mStates.push_back(state);
}

GameState* Game::popState() {
    GameState *pop = mStates.back();
    mStates.pop_back();
    return pop;
}

}