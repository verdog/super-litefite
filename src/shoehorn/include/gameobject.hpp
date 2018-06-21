/* gameobject.hpp
 * a game object is anything in a game that can change during gameplay
 * 
 * Josh Chandler
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace shoe
{

class GameObject : public sf::Sprite {
public:
    GameObject();
    ~GameObject();

    virtual void handleInput(const sf::Time &dTime);
    virtual void update(const sf::Time &dTime);

protected:
    sf::Vector2f mVelocity;
};

}
