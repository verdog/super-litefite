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
    init();
    setWindowTitle(title);
    mWindow.setVerticalSyncEnabled(60);
}

bool Game::init() {
    mInitialized = true;
    // placeholder?

    if (mStates.size() > 0) {
        std::cout << "topState use count at init = " << topState().use_count() << std::endl;
    }
    
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
                        std::cout << "RESTART\n";

                        std::shared_ptr<GameState> newState = topState()->clone();
                        std::cout << "topState use count = " << topState().use_count() << std::endl;
                        std::cout << "newState use count = " << newState.use_count()   << std::endl;
                        popState();

                        std::cout << "stateStack length after pop: " << mStates.size() << std::endl;

                        newState->cleanUp();
                        newState->init();
                        pushState(newState);

                        std::cout << "stateStack length after push: " << mStates.size() << std::endl;
                    }

                    if (e.key.code == sf::Keyboard::X) {
                        topState();
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
    std::cout << "topState use count after push = " << topState().use_count() << std::endl;
}

std::shared_ptr<GameState> Game::topState() {
    return mStates.back();
}

void Game::popState() {
    mStates.pop_back();
}

}