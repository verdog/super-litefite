/*
 * gamestate.cpp
 * basic game state
 * 
 * Josh Chandler
*/

#include "include/game.hpp"
// #include "include/gameobject.hpp"
#include "include/gamestate.hpp"

namespace shoe {

GameState::GameState(Game *game) 
: mGame {game}
{

}

void GameState::clear() {
    mGame->window().clear();
}

}