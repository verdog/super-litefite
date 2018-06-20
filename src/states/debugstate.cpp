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

DebugState::DebugState(shoe::Game *game) 
: GameState(game)
{
    loadTextures();
    init();
}

DebugState::~DebugState() {

}

void DebugState::loadTextures() {
    mTextureManager->loadTexture("g", "resources/bg.png");
    mTextureManager->getTexture("g")->setRepeated(true);
}

void DebugState::init() {
    shoe::GameObject *bg = new shoe::GameObject;
    bg->setTexture(*mTextureManager->getTexture("g"));
    bg->setTextureRect(sf::IntRect(0,0,mGame->window().getSize().x,mGame->window().getSize().y));

    mObjects.push_back(bg);
}

void DebugState::draw() {
    for (shoe::GameObject* o : mObjects) {
        mGame->window().draw(*o);
    }
}