/* game.hpp
 * basic game class
 * 
 * Josh Chandler
*/

#pragma once

#include <string>
#include <vector>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace shoe {

class GameState;
class ImageManager;

class Game {
public:
    Game(std::string title = "shoegame");

    bool init();
    bool run();

    // window management
    sf::RenderWindow& window();
    void setWindowTitle(std::string title);
    sf::RenderTexture& renderTexture();

    // view management
    void setGameSize(sf::Vector2u size);
    sf::Vector2u gameSize();
    void setGameSize(uint x, uint y);
    void setPixelScale(uint scale);
    uint pixelScale() { return mPixelScale; }

    // state management
    void pushState(std::shared_ptr<shoe::GameState> state);
    void popState();
    std::shared_ptr<GameState> topState();

private:
    // display
    sf::RenderWindow mWindow;
    sf::View mView;
    sf::Vector2u mGameResolution;
    unsigned int mPixelScale;
    sf::RenderTexture mRenderTexture;

    // states
    std::vector<std::shared_ptr<shoe::GameState>> mStates;

    // status bools
    bool mInitialized;
    bool mRunning;
};

}