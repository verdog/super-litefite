/* debugstate
 * for foolin'
 * 
 * Josh Chandler
*/

#include "../shoehorn/include/gameobject.hpp"
#include "../shoehorn/include/gamestate.hpp"
#include "../shoehorn/include/texturemanager.hpp"
#include "../shoehorn/include/game.hpp"
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

}

void DebugState::loadTextures() {
    mTextureManager->loadTexture("bg", "resources/img/bg.png");
    mTextureManager->getTexture("bg")->setRepeated(true);

    mTextureManager->loadTexture("player", "resources/img/player.png");
    mTextureManager->loadTexture("bricks", "resources/img/brik.png");
    mTextureManager->getTexture("bricks")->setRepeated(true);
}

void DebugState::init() {
    mFPS = new shoe::FpsCounter;
    mBackground = new shoe::GameObject;
    mBackground->setTexture(*mTextureManager->getTexture("bg"));
    mBackground->setTextureRect(sf::IntRect(0,0,mGame->window().getSize().x,mGame->window().getSize().y));
    mObjects.push_back(mBackground);

    mPlayer = new Player;
    mPlayer->setTexture(*mTextureManager->getTexture("player"), true);
    mObjects.push_back(mPlayer);

    Wallygon *wall = new Wallygon;
    wall->rot = 0;
    wall->setPrimitiveType(sf::PrimitiveType::TriangleFan);
    wall->append(sf::Vertex(sf::Vector2f(32, 32)));
    wall->append(sf::Vertex(sf::Vector2f(0, 0)));
    wall->append(sf::Vertex(sf::Vector2f(64, 0)));
    wall->append(sf::Vertex(sf::Vector2f(64, 64)));
    wall->append(sf::Vertex(sf::Vector2f(0, 64)));
    wall->append(sf::Vertex(sf::Vector2f(0, 0)));

    // wall->append(sf::Vertex(sf::Vector2f(300, 300)));
    // wall->append(sf::Vertex(sf::Vector2f(350, 300)));
    // wall->append(sf::Vertex(sf::Vector2f(400, 400)));
    // wall->append(sf::Vertex(sf::Vector2f(250, 400)));

    (*wall)[0].texCoords = sf::Vector2f(16, 16);
    (*wall)[1].texCoords = sf::Vector2f(0, 0);
    (*wall)[2].texCoords = sf::Vector2f(32, 0);
    (*wall)[3].texCoords = sf::Vector2f(32, 32);
    (*wall)[4].texCoords = sf::Vector2f(0, 32);
    (*wall)[5].texCoords = sf::Vector2f(0, 0);

    mWalls.push_back(wall);
    mWalls.push_back(wall);
}

void DebugState::update(const sf::Time &dTime) {
    for (shoe::GameObject* o : mObjects) {
        o->handleInput(dTime);
        o->update(dTime);
    }

    mFPS->tick();
}

void DebugState::draw() {
    for (shoe::GameObject* o : mObjects) {
        mGame->renderTexture().draw(*o);
    }
    sf::RenderStates states;
    sf::Transform transform;

    transform
        .translate(sf::Vector2f(-32, -32))
        .rotate(45)
        .translate(sf::Vector2f(32, 32))
        ;

    states.texture = mTextureManager->getTexture("bricks");
    states.transform = transform;

    mGame->renderTexture().draw(*mWalls[0], states);

    transform.combine(transform.getInverse());
    transform
        .rotate(45, sf::Vector2f(32, 32))
        ;

    states.transform = transform;

    mGame->renderTexture().draw(*mWalls[1], states);

    mGame->renderTexture().draw(*mFPS);
}