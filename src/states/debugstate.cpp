/* debugstate
 * for foolin'
 * 
 * Josh Chandler
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

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
#include "../include/lightmask.hpp"

#include "../include/player.hpp"

DebugState::DebugState(std::shared_ptr<shoe::Game> game) 
: GameState(game)
, mLightMaskk(new LightMask(mGame->gameSize().x, mGame->gameSize().y))
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

    // these should all be smart pointers, but i'm ignoring it because this is a debug state only

    mFPS = new shoe::FpsCounter;
    mBackground = new shoe::GameObject(this);
    mBackground->setTexture(*mTextureManager->getTexture("bg"));
    mBackground->setTextureRect(sf::IntRect(0,0,mGame->window().getSize().x,mGame->window().getSize().y));
    mObjects.push_back(mBackground);

    mPlayer = new Player(this);
    mPlayer->setTexture(*mTextureManager->getTexture("player"), true);
    mObjects.push_back(mPlayer);

    for (int i=0; i<5; i++) {
        Wallygon *wall = new Wallygon(this);
        wall->randomize(4 + i/2, random.int_(32, 128), mGame->gameSize());

        mWalls.push_back(wall);
    }

    LightSource *l1 = new LightSource(this, mPlayer);
    LightSource *l2 = new LightSource(this, mPlayer);

    l1->setColor(sf::Color(255, 220, 220)); // redish
    l2->setColor(sf::Color(220, 220, 255)); // blueish

    mLightSources.push_back(l1);
    mLightSources.push_back(l2);
}

void DebugState::cleanUp() {
    mObjects.clear();
    mWalls.clear();

    mLightSources.clear();
}

void DebugState::update(const sf::Time &dTime) {
    shoe::Random random;

    for (shoe::GameObject* o : mObjects) {
        o->handleInput(dTime);
        o->update(dTime);    
    }

    std::vector<shoe::GameObject*> tempWalls(mWalls.begin(), mWalls.end());
    mLightSources[0]->update(dTime);
    mLightSources[0]->makeVisibilityShape(tempWalls);

    mLightSources[1]->setPosition(sf::Vector2f(mGame->gameSize()) - mPlayer->getPosition());
    mLightSources[1]->makeVisibilityShape(tempWalls);

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
        drawOntoGame(*o);
        drawOntoGame(o->collisionPolygon());
    }

    mLightMaskk->reset();
    mLightMaskk->add(*mLightSources[0]);
    mLightMaskk->add(*mLightSources[1]);
    drawOntoGame(*mLightMaskk->sprite(), sf::RenderStates(sf::BlendMultiply));

    sf::RenderStates states;
    states.texture = mTextureManager->getTexture("bricks");

    for (Wallygon *w : mWalls) {
        drawOntoGame(*w, states);
        drawOntoGame(w->collisionPolygon());
    }

    for (LightSource *l : mLightSources) {
        drawOntoGame(*l);
    }

    // drawOntoGame(*mFPS);
}