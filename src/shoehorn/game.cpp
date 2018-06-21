/* game.cpp
 * basic game class
 * 
 * Josh Chandler
*/

#include <iostream>

#include "include/game.hpp"
#include "include/gamestate.hpp"

#include "include/texturemanager.hpp"

namespace shoe {

Game::Game(std::string title)
: mWindow (sf::VideoMode(256,256), "shoeGame")
, mPixelScale(1)
, mStates()
, mInitialized {false}
, mRunning {false}
{
    setWindowTitle(title);
    mWindow.setFramerateLimit(60);
}

bool Game::init() {
    mInitialized = true;
    // placeholder?
    return true;
}

bool Game::run() {
    if (!mInitialized) {
        init();
    }

    mRunning = true;

    sf::Time deltaTime;
    sf::Clock frameTimer;
    frameTimer.restart();

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

        deltaTime = frameTimer.getElapsedTime();
        frameTimer.restart();
        if (!mStates.empty()) {
            mStates.back()->clear();
            mStates.back()->update(deltaTime);
            mStates.back()->draw();
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

// view management
void Game::setGameSize(sf::Vector2u size) {
    setGameSize(size.x, size.y);
}

void Game::setGameSize(uint x, uint y) {
    mGameResolution = sf::Vector2u(x, y);
    mWindow.setSize(mPixelScale * mGameResolution);
    sf::View view(sf::FloatRect(0.f, 0.f, (float)mGameResolution.x, (float)mGameResolution.y));
    mWindow.setView(view);
}

void Game::setPixelScale(uint scale) {
    mPixelScale = scale;
    setGameSize(mGameResolution); // reset the view
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