/*
 * gamestate.hpp
 * basic game state
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>

namespace shoe {

class Game;
class GameObject;

class GameState {
public:
    GameState(Game *game);

    virtual void clear();
    virtual void update() {};
    virtual void display() {};

private:
    Game *mGame;
    std::vector<GameObject*> mObjects;
};

}