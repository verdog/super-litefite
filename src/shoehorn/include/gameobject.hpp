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

struct PhysicsProperties {
    PhysicsProperties() {
        drag = 1;
        friction = 1;
        bounce = 0;
    }

    float drag; // drag in air
    float friction; // drag against an object
    float bounce; // bounce off object
};

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

    PhysicsProperties physics() { return mPhysics; };

protected:
    GameState *mState;
    sf::Vector2f mVelocity;
    std::unique_ptr<CollisionPolygon> mCollisionPolygon;

    PhysicsProperties mPhysics;
};

}
