/* game.hpp
 * basic game class
 * 
 * Josh Chandler
*/

#pragma once

#include <string>
#include <vector>

#include "shoehorn.hpp"

namespace shoe {

class GameState;

class Game {
public:
    Game(std::string title);

    bool init();
    bool run();

    // window management
    sf::RenderWindow& window();
    void setWindowSize(uint x, uint y);
    void setWindowTitle(std::string title);

    // state management
    void pushState(GameState *state);
    GameState* popState();

private:
    // display
    sf::Vector2u mGameResolution;
    sf::Vector2u mWinResolution;
    unsigned int mPixelScale;
    sf::RenderWindow mWindow;
    sf::View mView;

    // states
    std::vector<GameState*> mStates;

    // status bools
    bool mInitialized;
    bool mRunning;
};

}