/* gameobject.hpp
 * a game object is anything in a game that can change during gameplay
 * 
 * Josh Chandler
*/

#pragma once

#include <memory>

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

    int id() const { return mId; }

    bool operator < (const GameObject b) const {
        return mId < b.id();
    }

protected:
    GameState *mState;
    sf::Vector2f mVelocity;
    std::shared_ptr<CollisionPolygon> mCollisionPolygon;

    PhysicsProperties mPhysics;

    const int mId;
    static int mNextId;
};

}
