/*
 * gamestate.hpp
 * basic game state
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

namespace shoe {

class Game;
class GameObject;
class TextureManager;

class GameState {
public:
    GameState(std::shared_ptr<Game> game);

    virtual std::shared_ptr<GameState> clone() const = 0;

    virtual void init() {};
    virtual void cleanUp() {};
    virtual void clear();
    virtual void update(const sf::Time &dTime);
    virtual void draw();
    virtual void display();

    void drawOntoGame(const sf::Drawable &thing, sf::RenderStates states = sf::RenderStates());

    bool loadTexture(std::string key, std::string path);
    sf::Texture* getTexture(std::string key);

    std::shared_ptr<shoe::Game> getGame() { return mGame; }

protected:
    std::shared_ptr<shoe::Game> mGame;
    std::vector<std::shared_ptr<GameObject>> mObjects;

    // texture management
    std::shared_ptr<TextureManager> mTextureManager;
};

}