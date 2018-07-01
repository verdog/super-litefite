/* gameobject.hpp
 * a game object is anything in a game that can change during gameplay
 * 
 * Josh Chandler
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace shoe
{

class GameState;
class CollisionPolygon;

class GameObject : public sf::Sprite {
public:
    GameObject(GameState *state);
    ~GameObject();

    virtual void handleInput(const sf::Time &dTime);
    virtual void update(const sf::Time &dTime);

    CollisionPolygon collisionPolygon() const;
    
    sf::Vector2f collidesWith(const GameObject &other) const;
    sf::Vector2f collidesWith(const CollisionPolygon &other) const;

    void makeIntoRegularShape(uint sides, uint radius);
    void makeIntoRect(sf::Vector2f size);

protected:
    GameState *mState;
    sf::Vector2f mVelocity;
    std::unique_ptr<CollisionPolygon> mCollisionPoly;
};

}
