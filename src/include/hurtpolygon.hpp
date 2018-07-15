/*
 * hurt polygon
 * hurts things.
 * 
 * Josh Chandler
*/

#pragma once

#include <iostream>

#include "../shoehorn/include/collisionpolygon.hpp"

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

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    bool mOpen;
    int mDamage;
};