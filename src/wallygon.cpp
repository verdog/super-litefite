/*
 * wallygon
 * 
 * Josh Chandler
*/

#include <iostream>

#include "shoehorn/include/random.hpp"

#include "include/wallygon.hpp"

Wallygon::Wallygon() 
: VertexArray() 
{

}

Wallygon::~Wallygon() {

}

// sets a random position and shape
void Wallygon::randomize(sf::Vector2u size) {
    return randomize(size.x, size.y);
}

void Wallygon::randomize(uint maxX, uint maxY) {
    shoe::Random random;
    mPosition = sf::Vector2f(random.int_(0, maxX), random.int_(0, maxY));

    std::cout << mPosition.x << " " << mPosition.y << std::endl;
}