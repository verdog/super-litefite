/* game.cpp
 * basic game class
 * 
 * Josh Chandler
*/

#include <iostream>

#include "include/game.hpp"

namespace shoe {

Game::Game(std::string title)
: mInitialized {false}
, mRunning {false}
{
    
}

bool Game::init() {
    mInitialized = true;

    mWindow.create(sf::VideoMode(256, 256), "shoeGame");

    return true;
}

bool Game::run() {
    if (!mInitialized) {
        std::cerr << "ERROR: run() called before init()! Exiting...\n";
        return false;
    }

    mRunning = true;

    while (mRunning) {
        sf::Event e;
        while (mWindow.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    mRunning = false;
                    break;
            
                default:
                    break;
            }   
        }

        mWindow.clear();

        // draw

        mWindow.display();
    }

    return true;
}

void Game::setWindowSize(uint x, uint y) {
    mWindow.setSize(sf::Vector2u(x, y));
}

void Game::setWindowTitle(std::string title) {
    mWindow.setTitle(title);
}

}