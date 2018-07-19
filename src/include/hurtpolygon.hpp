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
    HurtPolygon(int damage = 2);
    ~HurtPolygon();

    void open();
    void close();
    void toggle();

    void setDamage(int damage);
    int getDamage();

    void addVulnerability(const shoe::GameObject &object);
    void removeVulnerability(const shoe::GameObject &object);
    bool canHurt(const shoe::GameObject &object);
    std::set<shoe::GameObject>& getHurtList() { return mVulnerable; }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    bool mOpen;
    int mDamage;
    std::set<shoe::GameObject> mVulnerable;
};