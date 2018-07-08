/* debugstate
 * for foolin'
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>

#include "../../shoehorn/include/gamestate.hpp"

namespace shoe {
    class Game;
    class GameObject;
    class FpsCounter;
}

class LightSource;
class Player;
class Wallygon;

class DebugState : public shoe::GameState {
public:
    DebugState(shoe::Game *game);
    ~DebugState();

    DebugState* clone() const { return new DebugState(*this); }

    void loadTextures();
    void unLoadTextures();
    void init();
    void cleanUp();
    void update(const sf::Time &dTime);
    void draw();
    
    std::vector<Wallygon*> mWalls;
    shoe::FpsCounter *mFPS;
private:
    shoe::GameObject *mBackground;
    Player *mPlayer;

    std::vector<sf::RenderTexture*> mLightTextures;
    std::vector<LightSource*> mLightSources;
    std::vector<sf::VertexArray> mLightShapes;
    sf::RenderTexture *mLightMask;
    sf::Sprite mLightSprite;
};