/* game.hpp
 * basic game class
 * 
 * Josh Chandler
*/

#pragma once

#include <string>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace shoe {

class GameState;
class ImageManager;

class Game {
public:
    Game(std::string title);

    bool init();
    bool run();

    // window management
    sf::RenderWindow& window();
    void setWindowSize(uint x, uint y);
    void setWindowTitle(std::string title);

    // view management
    void setGameSize(sf::Vector2u size);
    void setGameSize(uint x, uint y);
    void setPixelScale(uint scale);

    // state management
    void pushState(GameState *state);
    GameState* popState();

private:
    // display
    sf::RenderWindow mWindow;
    sf::View mView;
    sf::Vector2u mGameResolution;
    sf::Vector2u mWinResolution;
    unsigned int mPixelScale;

    // states
    std::vector<GameState*> mStates;

    // status bools
    bool mInitialized;
    bool mRunning;
};

}