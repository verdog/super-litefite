/* debugstate
 * for foolin'
 * 
 * Josh Chandler
*/

#include <iostream>

#include "../shoehorn/include/gameobject.hpp"
#include "../shoehorn/include/collisionpolygon.hpp"
#include "../shoehorn/include/gamestate.hpp"
#include "../shoehorn/include/texturemanager.hpp"
#include "../shoehorn/include/game.hpp"
#include "../shoehorn/include/random.hpp"
#include "../shoehorn/include/fpscounter.hpp"

#include "include/debugstate.hpp"
#include "../include/wallygon.hpp"

#include "../include/player.hpp"

DebugState::DebugState(shoe::Game *game) 
: GameState(game)
{
    loadTextures();
    init();
}

DebugState::~DebugState() {
    cleanUp();
}

void DebugState::loadTextures() {
    mTextureManager->loadTexture("bg", "resources/img/bg.png");
    mTextureManager->getTexture("bg")->setRepeated(true);

    mTextureManager->loadTexture("player", "resources/img/player.png");
    mTextureManager->loadTexture("bricks", "resources/img/brik.png");
    mTextureManager->getTexture("bricks")->setRepeated(true);
}

void DebugState::init() {
    shoe::Random random;

    mFPS = new shoe::FpsCounter;
    mBackground = new shoe::GameObject(this);
    mBackground->setTexture(*mTextureManager->getTexture("bg"));
    mBackground->setTextureRect(sf::IntRect(0,0,mGame->window().getSize().x,mGame->window().getSize().y));
    mObjects.push_back(mBackground);

    mPlayer = new Player(this);
    mPlayer->setTexture(*mTextureManager->getTexture("player"), true);
    mObjects.push_back(mPlayer);

    for (int i=0; i<1; i++) {
        Wallygon *wall = new Wallygon;
        wall->setPrimitiveType(sf::PrimitiveType::TriangleFan);
        wall->randomize(4 + i, random.int_(32, 198), mGame->gameSize());
        wall->mRot = 0;
        mWalls.push_back(wall);
    }
}

void DebugState::cleanUp() {
    mObjects.clear();
    mWalls.clear();
}

void DebugState::update(const sf::Time &dTime) {
    for (shoe::GameObject* o : mObjects) {
        o->handleInput(dTime);
        o->update(dTime);
    }

    mFPS->tick();
}

void DebugState::draw() {
    for (shoe::GameObject *o : mObjects) {
        sf::Transform t;
        t.translate(o->getPosition());
        sf::RenderStates states(t);
        mGame->renderTexture().draw(*o);
        mGame->renderTexture().draw(o->collisionPolygon(), states);
    }

    sf::RenderStates states;
    states.texture = mTextureManager->getTexture("bricks");

    for (Wallygon *w : mWalls) {
        states.transform = w->collisionPolygon().transform();
        mGame->renderTexture().draw(*w, states);
        mGame->renderTexture().draw(w->collisionPolygon(), sf::RenderStates(sf::Transform(w->collisionPolygon().transform())));
    }

    // mGame->renderTexture().draw(*mFPS);
}