/* game.cpp
 * basic game class
 * 
 * Josh Chandler
*/

#include <iostream>
#include <memory>

#include "include/game.hpp"
#include "include/gamestate.hpp"

#include "include/texturemanager.hpp"

namespace shoe {

Game::Game(std::string title)
: mWindow (sf::VideoMode(256,256), title)
, mPixelScale(1)
, mStates()
, mInitialized {false}
, mRunning {false}
{
    setWindowTitle(title);
    mWindow.setVerticalSyncEnabled(60);
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
                    if (e.key.code == sf::Keyboard::R) {
                        std::shared_ptr<GameState> newState = popState()->clone();

                        std::cout << "RESTART\n";

                        newState->cleanUp();
                        newState->init();
                        pushState(newState);
                    }

                    if (e.key.code == sf::Keyboard::X) {
                        popState();
                    }

                    if (e.key.code == sf::Keyboard::Escape) {
                        mRunning = false;
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

sf::RenderTexture& Game::renderTexture() {
    return mRenderTexture;
}

// view management
void Game::setGameSize(sf::Vector2u size) {
    setGameSize(size.x, size.y);
}

void Game::setGameSize(uint x, uint y) {
    mGameResolution = sf::Vector2u(x, y);

    mRenderTexture.create(mGameResolution.x, mGameResolution.y);
    mRenderTexture.setSmooth(false);

    mWindow.setSize(mPixelScale * mGameResolution);
    sf::View view(sf::FloatRect(0.f, 0.f, (float)mGameResolution.x, (float)mGameResolution.y));
    mWindow.setView(view);
}

sf::Vector2u Game::gameSize() {
    return mGameResolution;
}

void Game::setPixelScale(uint scale) {
    mPixelScale = scale;
    setGameSize(mGameResolution); // reset the view
}

void Game::setWindowTitle(std::string title) {
    mWindow.setTitle(title);
}

// state management
void Game::pushState(std::shared_ptr<shoe::GameState> state) {
    mStates.push_back(state);
}

std::shared_ptr<GameState> Game::popState() {
    std::shared_ptr<GameState> pop = mStates.back();
    mStates.pop_back();
    return pop;
}

}