/* game.cpp
 * basic game class
 * 
 * Josh Chandler
*/

#include <iostream>

#include "include/game.hpp"

namespace shoe {

Game::Game(int x, int y, std::string title) {
    mWindow.create(sf::VideoMode(x, y), title);
    mWindow.setFramerateLimit(60);
}

}