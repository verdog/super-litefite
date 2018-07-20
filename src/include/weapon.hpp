/*
 * weapon
 * stabby stab
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>

#include "../shoehorn/include/gameobject.hpp"

class HurtPolygon;

class Weapon : public shoe::GameObject {
public:
    Weapon(shoe::GameState *state);

    void setPosition(sf::Vector2f position);
    void setRotation(float rotation);

    void addVulnerability(const shoe::GameObject &object);
    void removeVulnerability(const shoe::GameObject &object);
    bool canHurt(const shoe::GameObject &object);

    virtual void activate();
    void update(const sf::Time &dTime);
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    std::vector<std::shared_ptr<HurtPolygon>> mHurtPolygons;
};