/*
 * gamestate.hpp
 * basic game state
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>
#include <string>

namespace shoe {

class Game;
class GameObject;
class ImageManager;

class GameState {
public:
    GameState(Game *game);

    virtual void clear();
    virtual void update() {};
    virtual void draw();
    virtual void display();

    bool loadImage(std::string key, std::string path);
    sf::Texture* getImage(std::string key);

private:
    Game *mGame;
    std::vector<GameObject*> mObjects;

    // image management
    ImageManager *mImageManager;
};

}