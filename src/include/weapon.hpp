/*
 * weapon
 * stabby stab
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>

#include "../shoehorn/include/gameobject.hpp"

class HurtPolygonAnimator;

class Weapon : public shoe::GameObject {
public:
    Weapon(shoe::GameState *state);

    void setHurtPolygonPosition(sf::Vector2f position);
    void rotateHurtPolygon(float angle);
    void setHurtPolygonRotation(float rotation);

    void addVulnerability(const shoe::GameObject &object);
    void removeVulnerability(const shoe::GameObject &object);
    bool canHurt(const shoe::GameObject &object);

    virtual void activate();
    void update(const sf::Time &dTime);
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    std::shared_ptr<HurtPolygonAnimator> mHurtPolygons;
};