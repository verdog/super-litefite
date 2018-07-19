/* debugstate
 * for foolin'
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>
#include <memory>

#include "../../shoehorn/include/gamestate.hpp"

namespace shoe {
    class Game;
    class GameObject;
    class FpsCounter;
    template <typename T> class ObjectManager;
}

class LightSource;
class HurtPolygon;
class LightMask;
class Player;
class Wallygon;

class DebugState : public shoe::GameState {
public:
    DebugState(shoe::Game *game);
    ~DebugState();

    std::shared_ptr<GameState> clone() const { return std::shared_ptr<DebugState>(new DebugState(*this)); }

    void loadTextures();
    void unLoadTextures();
    void init();
    void cleanUp();
    void update(const sf::Time &dTime);
    void draw();
    
    std::vector<std::shared_ptr<Wallygon>> mWalls;
    shoe::FpsCounter *mFPS;
private:
    std::shared_ptr<LightMask> mLightMask;

    bool keypress;
};