/* debugstate
 * for foolin'
 * 
 * Josh Chandler
*/

#pragma once

#include "../../shoehorn/include/gamestate.hpp"

namespace shoe {
    class Game;
    class GameObject;
}

class Player;

class DebugState : public shoe::GameState {
public:
    DebugState(shoe::Game *game);
    ~DebugState();

    void loadTextures();
    void unLoadTextures();
    void init();
    void update(const sf::Time &dTime);
    void draw();
private:
    shoe::GameObject *mBackground;
    Player *mPlayer;
};