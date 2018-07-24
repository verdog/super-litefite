/*
 * super litefite
 * the game
 * 
 * Josh Chandler
*/

#include <iostream>
using std::cout;
using std::cin;
using std::end;

#include "include/super-litefite.hpp"
#include "shoehorn/include/gamestate.hpp"

#include "states/include/debugstate.hpp"

SuperLiteFite::SuperLiteFite() 
: shoe::Game("super litefite")
{

}

bool SuperLiteFite::run() {
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

                        std::shared_ptr<shoe::GameState> newState = topState()->clone();
                        std::cout << "topState use count = " << topState().use_count() << std::endl;
                        std::cout << "newState use count = " << newState.use_count()   << std::endl;
                        popState();

                        std::cout << "stateStack length after pop: " << mStates.size() << std::endl;

                        newState->cleanUp();
                        newState->init();
                        pushState(newState);
                    }

                    if (e.key.code == sf::Keyboard::X) {
                        popState();
                    }

                    if (e.key.code == sf::Keyboard::Z) {
                        std::shared_ptr<shoe::GameState> newState(new DebugState(this));
                        pushState(newState);
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
            topState()->clear();
            topState()->update(deltaTime);
            topState()->draw();
            topState()->display();
        } else {
            mRunning = false;
            std::cerr << "ERROR: No state on state stack!\n"; 
        }
    }

    return true;
}