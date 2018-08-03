/*
 * hurt polygon
 * hurts things.
 * 
 * Josh Chandler
*/

#include "shoehorn/include/gamestate.hpp"
#include "shoehorn/include/collisionpolygon.hpp"

#include "include/hurtpolygon.hpp"

HurtPolygon::HurtPolygon(int damage)
: shoe::CollisionPolygon()
, mOpen {false}
, mDamage {damage}
{
    makeIntoRegularShape(4, 16);
}

bool HurtPolygon::isOpen() {
    return mOpen;
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

void HurtPolygon::addVulnerability(const shoe::GameObject &object) {
    mVulnerable.insert(object);
}

void HurtPolygon::removeVulnerability(const shoe::GameObject &object) {
    mVulnerable.erase(object);
}

bool HurtPolygon::canHurt(const shoe::GameObject &object) {
    // make sure the hitbox is open and the object is in the vulnerable vector
    return mOpen && !(mVulnerable.find(object) == mVulnerable.end());
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
