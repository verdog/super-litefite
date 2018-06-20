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
    mTextureManager->loadTexture("shu", "resources/shu.png");
}

void DebugState::init() {
    shoe::GameObject *object = new shoe::GameObject;
    mObjects.push_back(object);

    object->setTexture(*mTextureManager->getTexture("shu"), true);
}

void DebugState::draw() {
    for (shoe::GameObject* o : mObjects) {
        mGame->window().draw(*o);
    }
}