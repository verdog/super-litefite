/*
 * wallygon
 * 
 * Josh Chandler
*/

#include <iostream>
#include <algorithm>
#include <cmath>

#include "shoehorn/include/random.hpp"
#include "shoehorn/include/gameobject.hpp"
#include "shoehorn/include/collisionpolygon.hpp"

#include "include/wallygon.hpp"

const double pi = std::acos(-1);

Wallygon::Wallygon(shoe::GameState *state)
: GameObject(state)
, mCPolygon(new shoe::CollisionPolygon) 
{
    mVertices.setPrimitiveType(sf::PrimitiveType::TriangleFan);
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
    
    mRad = radius;

    mVertices.clear();
    mVertices.resize(sides + 2);

    std::vector<sf::Vector2f> points;
    uint size = random.int_(radius*2/3, radius);

    // pick {size} distances and angles
    for (uint i=0; i<mVertices.getVertexCount()-2; i++) {
        uint angle = random.double_(i*360/(mVertices.getVertexCount()-2), (i+1)*360/(mVertices.getVertexCount()-2));

        points.push_back(sf::Vector2f(
            size * std::cos(angle*pi/180.f),
            size * std::sin(angle*pi/180.f)
        ));
    }

    // set points
    mVertices[0].position = sf::Vector2f(0,0);

    for (uint i=1; i<mVertices.getVertexCount()-1; i++) {
        mVertices[i].position = points[i-1];
    }

    mVertices[mVertices.getVertexCount()-1].position = mVertices[1].position;

    // texture points
    for (uint i=0; i<mVertices.getVertexCount(); i++) {
        sf::Transform t;
        t = t.rotate(random.int_(-25,25)).scale(random.double_(.25,1),random.double_(0.25,1));
        
        mVertices[i].texCoords = t.transformPoint(mVertices[i].position);
    }

    // update collision polygon
    sf::VertexArray collisionVerts;
    collisionVerts.resize(mVertices.getVertexCount()-2);

    for (uint i=1; i<mVertices.getVertexCount()-1; i++) {
        collisionVerts[i-1].position = mVertices[i].position;
    }
    mCPolygon->loadPointsFromVertexArray(collisionVerts);

    setPosition(sf::Vector2f(random.int_(minX, maxX), random.int_(minY, maxY)));
}

void Wallygon::setPosition(sf::Vector2f position) {
    shoe::GameObject::setPosition(position);
    mCollisionPoly->setPosition(position);
    std::cout << mCollisionPoly->getTransform().transformPoint(sf::Vector2f()).x << std::endl;
}

sf::Vector2f Wallygon::collidesWith(const shoe::GameObject &other) {
    return mCPolygon->collidesWith(other.collisionPolygon());
}

shoe::CollisionPolygon Wallygon::collisionPolygon() {
    return *mCPolygon;   
}

void Wallygon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform = getTransform();
    target.draw(mVertices, states);
}