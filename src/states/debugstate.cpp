/* debugstate
 * for foolin'
 * 
 * Josh Chandler
*/

#include "include/debugstate.hpp"
#include "../shoehorn/include/gameobject.hpp"
#include "../shoehorn/include/gamestate.hpp"
#include "../shoehorn/include/texturemanager.hpp"
#include "../shoehorn/include/game.hpp"

#include "../include/player.hpp"

DebugState::DebugState(shoe::Game *game) 
: GameState(game)
{
    loadTextures();
    init();
}

DebugState::~DebugState() {

}

void DebugState::loadTextures() {
    mTextureManager->loadTexture("bg", "resources/img/mugs.png");
    mTextureManager->getTexture("bg")->setRepeated(true);

    mTextureManager->loadTexture("player", "resources/img/player.png");
}

void DebugState::init() {
    mBackground = new shoe::GameObject;
    mBackground->setTexture(*mTextureManager->getTexture("bg"));
    mBackground->setTextureRect(sf::IntRect(0,0,mGame->window().getSize().x,mGame->window().getSize().y));
    mObjects.push_back(mBackground);

    mPlayer = new Player;
    mPlayer->setTexture(*mTextureManager->getTexture("player"), true);
    mObjects.push_back(mPlayer);
}

void DebugState::update(const sf::Time &dTime) {
    for (shoe::GameObject* o : mObjects) {
        o->handleInput(dTime);
        o->update(dTime);
    }
}

void DebugState::draw() {
    for (shoe::GameObject* o : mObjects) {
        mGame->renderTexture().draw(*o);
    }
}