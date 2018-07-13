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
, mLightMask(new LightMask(mGame->gameSize().x, mGame->gameSize().y))
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
    mObjects.push_back(std::shared_ptr<shoe::GameObject>(new shoe::GameObject(this)));
    mObjects.back()->setTexture(*mTextureManager->getTexture("bg"));
    mObjects.back()->setTextureRect(sf::IntRect(0,0,mGame->window().getSize().x,mGame->window().getSize().y));

    std::shared_ptr<Player> p1 = std::shared_ptr<Player>(new Player(this));
    std::shared_ptr<Player> p2 = std::shared_ptr<Player>(new Player(this));
    p1->setTexture(*mTextureManager->getTexture("player"), true);
    p2->setTexture(*mTextureManager->getTexture("player"), true);

    mPlayers.push_back(p1);
    mPlayers.push_back(p2);

    mObjects.push_back(p1);
    mObjects.push_back(p2);

    for (int i=0; i<5; i++) {
        std::shared_ptr<Wallygon> wall = std::shared_ptr<Wallygon>(new Wallygon(this));
        wall->randomize(4 + i/2, random.int_(32, 128), mGame->gameSize());

        mWalls.push_back(wall);
    }

    LightSource *l1 = new LightSource(this, p1);
    LightSource *l2 = new LightSource(this, p2);

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

    for (std::shared_ptr<shoe::GameObject> o : mObjects) {
        o->handleInput(dTime);
        o->update(dTime);
    }

    std::vector<std::shared_ptr<shoe::GameObject>> tempWalls(mWalls.begin(), mWalls.end());
    mLightSources[0]->update(dTime);
    mLightSources[0]->makeVisibilityShape(tempWalls);

    mPlayers[1]->setPosition(sf::Vector2f(mGame->gameSize()) - mPlayers[0]->getPosition());
    mPlayers[1]->update(dTime);
    mLightSources[1]->update(dTime);
    mLightSources[1]->makeVisibilityShape(tempWalls);

    for (uint i=0; i<mWalls.size(); i++) {
        std::shared_ptr<Wallygon> w = mWalls[i];

        std::vector<std::shared_ptr<Wallygon>> sans = mWalls;
        sans.erase(sans.begin() + i);
        std::random_shuffle(sans.begin(), sans.end());

        for (std::shared_ptr<Wallygon> sw : sans) {
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

    for (std::shared_ptr<shoe::GameObject> o : mObjects) {
        drawOntoGame(*o);
        drawOntoGame(o->collisionPolygon());
    }

    mLightMask->reset();
    mLightMask->add(*mLightSources[0]);
    mLightMask->add(*mLightSources[1]);
    drawOntoGame(*mLightMask->sprite(), sf::RenderStates(sf::BlendMultiply));

    sf::RenderStates states;
    states.texture = mTextureManager->getTexture("bricks");

    for (std::shared_ptr<Wallygon> w : mWalls) {
        drawOntoGame(*w, states);
        drawOntoGame(w->collisionPolygon());
    }

    for (LightSource *l : mLightSources) {
        drawOntoGame(*l);
    }

    // drawOntoGame(*mFPS);
}