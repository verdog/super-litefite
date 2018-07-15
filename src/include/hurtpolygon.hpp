/*
 * hurt polygon
 * hurts things.
 * 
 * Josh Chandler
*/

#pragma once

#include <iostream>
#include <vector>
#include <set>

#include "../shoehorn/include/collisionpolygon.hpp"
#include "../shoehorn/include/gameobject.hpp"

class HurtPolygon : public shoe::CollisionPolygon {
public:
    HurtPolygon();
    HurtPolygon(int damage);
    ~HurtPolygon();

    void open();
    void close();
    void toggle();

    void setDamage(int damage);
    int getDamage();

    void addImmunity(const shoe::GameObject &object);
    void removeImmunity(const shoe::GameObject &object);

    bool canHurt(const shoe::GameObject &object);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    bool mOpen;
    int mDamage;
    std::set<shoe::GameObject> mImmune;
};