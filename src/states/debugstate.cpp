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
#include "../shoehorn/include/objectmanager.hpp"

#include "include/debugstate.hpp"
#include "../include/wallygon.hpp"
#include "../include/lightsource.hpp"
#include "../include/lightmask.hpp"
#include "../include/player.hpp"
#include "../include/hurtpolygon.hpp"
#include "../include/weapon.hpp"

DebugState::DebugState(std::shared_ptr<shoe::Game> game) 
: GameState(game)
, mLightMask(new LightMask(mGame->gameSize().x, mGame->gameSize().y))
{
    loadTextures();
    init();
    keypress = false;
}

DebugState::~DebugState() {
    std::cout << "~DebugState()\n";
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
    mObjects.push_back(std::shared_ptr<shoe::GameObject>(new shoe::GameObject(this)));
    mObjects.back()->setTexture(*mTextureManager->getTexture("bg"));
    mObjects.back()->setTextureRect(sf::IntRect(0,0,mGame->window().getSize().x,mGame->window().getSize().y));

    std::shared_ptr<Player> p1 = std::shared_ptr<Player>(new Player(this));
    std::shared_ptr<Player> p2 = std::shared_ptr<Player>(new Player(this));
    p1->setTexture(*mTextureManager->getTexture("player"), true);
    p2->setTexture(*mTextureManager->getTexture("player"), true);
    p2->setPosition(sf::Vector2f(mGame->gameSize()) - p1->getPosition());
    p2->toggleReverse();

    float low = 200;
    float high = 232;

    p1->getLightSource().setColor(sf::Color(high, low, low));
    p2->getLightSource().setColor(sf::Color(low, low, high));

    mObjects.push_back(p1);
    mObjects.push_back(p2);

    for (int i=0; i<3; i++) {
        std::shared_ptr<Wallygon> wall = std::shared_ptr<Wallygon>(new Wallygon(this));
        wall->randomize(4 + i/2, random.int_(32, 128), mGame->gameSize());

        mWalls.push_back(wall);
    }
}

void DebugState::cleanUp() {
    std::cout << "DebugState::cleanUp()\n";
    mObjects.clear();
    mWalls.clear();
    hurtPolygons.clear();
}

void DebugState::update(const sf::Time &dTime) {
    shoe::Random random;

    mLightMask->reset(sf::Color::Black);

    int player = 0;

    for (std::shared_ptr<shoe::GameObject> o : mObjects) {
        o->handleInput(dTime);
        o->update(dTime);

        if (std::shared_ptr<Player> p = std::dynamic_pointer_cast<Player>(o); p) {
            mLightMask->add(p->getLightSource());

            // PLACEHOLDER >:0
            // if (!keypress) {
            //     if (player == 0) {
            //         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            //             // p->getLightSource().toggle();
            //             p->getHurtPolygon().toggle();
            //             keypress = true;
            //         }
            //     } else {
            //         if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            //             p->getLightSource().toggle();
            //             keypress = true;
            //         }
            //     }
            // } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            //     keypress = false;
            // }

            player++;
        }
    }

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

        if (std::shared_ptr<Player> p = std::dynamic_pointer_cast<Player>(o); p) {
            drawOntoGame(p->getLightSource());
            drawOntoGame(p->getWeapon());
        }
    }

    drawOntoGame(mLightMask->sprite(), sf::RenderStates(sf::BlendMultiply));

    sf::RenderStates states;
    states.texture = mTextureManager->getTexture("bricks");

    for (std::shared_ptr<Wallygon> w : mWalls) {
        drawOntoGame(*w, states);
        drawOntoGame(w->collisionPolygon());
    }

    // drawOntoGame(*mFPS);
}