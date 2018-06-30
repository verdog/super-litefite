/*
 * wallygon
 * 
 * Josh Chandler
*/

#include <iostream>
#include <algorithm>
#include <cmath>

#include "shoehorn/include/random.hpp"

#include "include/wallygon.hpp"

const double pi = std::acos(-1);

Wallygon::Wallygon() 
: VertexArray() 
{
    mRad = 128;
}

Wallygon::~Wallygon() {

}

// sets a random position and shape
void Wallygon::randomize(uint sides, uint radius, sf::Vector2u size) {
    return randomize(sides, radius, size.x, size.y);
}

void Wallygon::randomize(uint sides, uint radius, uint maxX, uint maxY) {
    shoe::Random random;

    float tweak = .2;

    uint minX = maxX * tweak;
    uint minY = maxY * tweak;
    maxX = maxX * (1 - tweak);
    maxY = maxY * (1 - tweak);

    mPosition = sf::Vector2f(random.int_(minX, maxX), random.int_(minY, maxY));
    mRad = radius;

    clear();
    resize(sides + 2);

    std::vector<sf::Vector2f> points;
    uint size = radius*2/3;

    // pick {size} distances and angles
    for (uint i=0; i<getVertexCount()-2; i++) {
        size = std::clamp(size+random.int_(-(int)radius/2, radius/2), radius*1/3, radius);
        uint angle = random.double_(i*360/(getVertexCount()-2), (i+1)*360/(getVertexCount()-2));

        points.push_back(sf::Vector2f(
            size * std::cos(angle*pi/180.f),
            size * std::sin(angle*pi/180.f)
        ));
    }

    // set points
    (*this)[0].position = sf::Vector2f(0,0);

    for (uint i=1; i<getVertexCount()-1; i++) {
        (*this)[i].position = points[i-1];
    }

    (*this)[getVertexCount()-1].position = (*this)[1].position;
}