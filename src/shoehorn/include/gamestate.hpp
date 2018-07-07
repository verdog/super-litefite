/*
 * gamestate.hpp
 * basic game state
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

namespace shoe {

class Game;
class GameObject;
class TextureManager;

class GameState {
public:
    GameState(Game *game);

    virtual GameState* clone() const = 0;

    virtual void init() {};
    virtual void cleanUp() {};
    virtual void clear();
    virtual void update(const sf::Time &dTime);
    virtual void draw();
    virtual void display();

    bool loadTexture(std::string key, std::string path);
    sf::Texture* getTexture(std::string key);

    shoe::Game* getGame() { return mGame; }

protected:
    Game *mGame;
    std::vector<GameObject*> mObjects;

    // texture management
    TextureManager *mTextureManager;
};

}