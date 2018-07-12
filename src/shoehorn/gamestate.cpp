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

GameState::GameState(std::shared_ptr<shoe::Game> game) 
: mGame {game}
, mTextureManager( new TextureManager ) // shared_ptr
{
    
}

void GameState::clear() {
    mGame->renderTexture().clear();
    mGame->window().clear();
}

void GameState::update(const sf::Time &dTime) {
    
}

void GameState::draw() {
    
}

void GameState::display() {
    mGame->renderTexture().display();
    mGame->window().draw(sf::Sprite(mGame->renderTexture().getTexture()));
    mGame->window().display();
}

void GameState::drawOnGame(const sf::Drawable &thing, sf::RenderStates states) {
    mGame->renderTexture().draw(thing, states);
}

bool GameState::loadTexture(std::string key, std::string path) {
    return mTextureManager->loadTexture(key, path);
}

sf::Texture* GameState::getTexture(std::string key) {
    return mTextureManager->getTexture(key);
}

}