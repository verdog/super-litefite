/* game.hpp
 * basic game class
 * 
 * Josh Chandler
*/

#pragma once

#include <string>

#include "shoehorn.hpp"

namespace shoe {

class Game {
public:
    Game(int x, int y, std::string title);
private:
    // display
    sf::IntRect mResolution;
    sf::RenderWindow mWindow;
    sf::View mView;
};

}