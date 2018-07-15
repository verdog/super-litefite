/*
 * hurt polygon
 * hurts things.
 * 
 * Josh Chandler
*/

#include "shoehorn/include/gamestate.hpp"
#include "shoehorn/include/collisionpolygon.hpp"

#include "include/hurtpolygon.hpp"

HurtPolygon::HurtPolygon()
: shoe::CollisionPolygon()
, mOpen {false}
, mDamage {1}
{
}

HurtPolygon::HurtPolygon(int damage)
: shoe::CollisionPolygon()
, mOpen {false}
, mDamage {damage}
{
    std::cout << "HurtPolygon()\n";
    makeIntoRegularShape(5, 16);
}

HurtPolygon::~HurtPolygon() {
    //
}

void HurtPolygon::open() {
    mOpen = true;
}

void HurtPolygon::close() {
    mOpen = false;
}

void HurtPolygon::toggle() {
    mOpen = mOpen ? false : true;
    std::cout << "mOpen is now " << mOpen << std::endl;
}

void HurtPolygon::setDamage(int damage) {
    mDamage = damage;
}

int HurtPolygon::getDamage() {
    return mDamage;
}

void HurtPolygon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // same as collisionpolygon::draw, except it colors it
    sf::VertexArray va = mVertexArray;
    
    if (va.getVertexCount() != 0) {
        va.append(va[0]);
    }

    sf::Color drawColor = mOpen ? sf::Color::Red : sf::Color::Black;

    for (uint i=0; i<va.getVertexCount(); i++) {
        va[i].color = drawColor;
    }

    states.transform = getTransform();

    target.draw(va, states);
}
