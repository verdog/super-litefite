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
    Game(std::string title);

    bool init();
    bool run();

    // window management
    void setWindowSize(uint x, uint y);
    void setWindowTitle(std::string title);
private:
    // display
    sf::Vector2u mGameResolution;
    sf::Vector2u mWinResolution;
    unsigned int mPixelScale;
    sf::RenderWindow mWindow;
    sf::View mView;

    // status bools
    bool mInitialized;
    bool mRunning;
};

}