/*
 * gamestate.cpp
 * basic game state
 * 
 * Josh Chandler
*/

#include "include/game.hpp"
#include "include/gamestate.hpp"
#include "include/texturemanager.hpp"

namespace shoe {

GameState::GameState(Game *game) 
: mGame {game}
, mTextureManager( new TextureManager )
{
    
}

void GameState::clear() {
    mGame->window().clear();
}

void GameState::update(const sf::Time &dTime) {
    
}

void GameState::draw() {
    
}

void GameState::display() {
    mGame->window().display();
}

bool GameState::loadTexture(std::string key, std::string path) {
    return mTextureManager->loadTexture(key, path);
}

sf::Texture* GameState::getTexture(std::string key) {
    return mTextureManager->getTexture(key);
}

}