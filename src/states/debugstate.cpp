/* debugstate
 * for foolin'
 * 
 * Josh Chandler
*/

#include <vector>
#include <iostream>
#include <algorithm>

#include "../shoehorn/include/gameobject.hpp"
#include "../shoehorn/include/collisionpolygon.hpp"
#include "../shoehorn/include/gamestate.hpp"
#include "../shoehorn/include/texturemanager.hpp"
#include "../shoehorn/include/game.hpp"
#include "../shoehorn/include/random.hpp"
#include "../shoehorn/include/fpscounter.hpp"

#include "include/debugstate.hpp"
#include "../include/wallygon.hpp"
#include "../include/lightsource.hpp"

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

    for (int i=0; i<2; i++) {
        Wallygon *wall = new Wallygon(this);
        wall->randomize(4 + i/2, random.int_(32, 128), mGame->gameSize());

        mWalls.push_back(wall);
    }

    LightSource *light = new LightSource(this, mPlayer);
    mObjects.push_back(light);
}

void DebugState::cleanUp() {
    mObjects.clear();
    mWalls.clear();
}

void DebugState::update(const sf::Time &dTime) {
    shoe::Random random;

    for (shoe::GameObject* o : mObjects) {
        o->handleInput(dTime);
        o->update(dTime);

        if (LightSource *light = dynamic_cast<LightSource*>(o)) {
            std::vector<shoe::GameObject*> tempWalls(mWalls.begin(), mWalls.end());
            light->makeVisibilityShape(tempWalls);
        }
    }

    for (uint i=0; i<mWalls.size(); i++) {
        Wallygon *w = mWalls[i];

        std::vector<Wallygon*> sans = mWalls;
        sans.erase(sans.begin() + i);
        std::random_shuffle(sans.begin(), sans.end());

        for (Wallygon *sw : sans) {
            sf::Vector2f MTA = w->collisionPolygon().collidesWith(sw->collisionPolygon());
            if (MTA != sf::Vector2f(0, 0)) {
                w->move(MTA * 0.2f);
                break;
            }
        }
    }

    mFPS->tick();
}

void DebugState::draw() {
    for (shoe::GameObject *o : mObjects) {
        mGame->renderTexture().draw(*o);
        mGame->renderTexture().draw(o->collisionPolygon());
    }

    sf::RenderStates states;
    states.texture = mTextureManager->getTexture("bricks");

    for (Wallygon *w : mWalls) {
        mGame->renderTexture().draw(*w, states);
        mGame->renderTexture().draw(w->collisionPolygon());
    }

    mGame->renderTexture().draw(*mFPS);
}