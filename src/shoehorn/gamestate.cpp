/*
 * gamestate.cpp
 * basic game state
 * 
 * Josh Chandler
*/

#include "include/game.hpp"
#include "include/gamestate.hpp"
#include "include/imagemanager.hpp"

namespace shoe {

GameState::GameState(Game *game) 
: mGame {game}
, mImageManager( new ImageManager )
{
    loadImage("shu", "resources/shu.png");
}

void GameState::clear() {
    mGame->window().clear();
}

void GameState::draw() {
    sf::Sprite spr;
    spr.setTexture(*getImage("shu"));
    spr.setScale(1.f, 1.f);
    mGame->window().draw(spr);
}

void GameState::display() {
    mGame->window().display();
}

bool GameState::loadImage(std::string key, std::string path) {
    return mImageManager->loadImage(key, path);
}

sf::Texture* GameState::getImage(std::string key) {
    return mImageManager->getImage(key);
}

}