/*
 * collision polygon
 *
 * uses SAT to check for collisions with other polygons
 *  
 * Josh Chandler
*/

#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "include/collisionpolygon.hpp"
#include "include/vector2math.hpp"

const double pi = std::acos(-1);

namespace shoe {

CollisionPolygon::CollisionPolygon() 
{
    //
}

CollisionPolygon::~CollisionPolygon() {
    //
}

void CollisionPolygon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::VertexArray va = mVertexArray;
    
    if (va.getVertexCount() != 0) {
        va.append(va[0]);
    }

    states.transform = getTransform();

    target.draw(va, states);
}

void CollisionPolygon::loadPointsFromVertexArray(const sf::VertexArray &verts) {
    mVertexArray.clear();
    mVertexArray.resize(verts.getVertexCount());
    mVertexArray.setPrimitiveType(sf::PrimitiveType::LineStrip);

    for (uint i = 0; i < verts.getVertexCount(); i++) {
        mVertexArray[i] = verts[i];
    }
}

void CollisionPolygon::makeIntoRegularShape(uint sides, uint radius) {
    mVertexArray.clear();
    mVertexArray.resize(sides);
    mVertexArray.setPrimitiveType(sf::PrimitiveType::LineStrip);

    float angle = 0;
    float increment = 360.f/sides;

    for (uint i=0; i<getVertexCount(); i++) {
        mVertexArray[i].position = sf::Vector2f(
            radius * std::cos(angle*pi/180.f),
            radius * std::sin(angle*pi/180.f)
        );
        angle += increment;
    }
}

sf::Vector2f CollisionPolygon::getMidpoint() const {
    sf::Vector2f midpoint;
    for (uint i=0; i<mVertexArray.getVertexCount(); i++) {
        midpoint += getTransform().transformPoint(Vector2Math::toVector2f(mVertexArray[i].position));
    }
    return midpoint/(float)mVertexArray.getVertexCount();
}

Collision CollisionPolygon::collidesWith(const CollisionPolygon &other) {
    std::vector<sf::Vector2f> normals = getNormals();
    std::vector<sf::Vector2f> otherNormals = other.getNormals();
    normals.reserve(otherNormals.size());
    normals.insert(normals.end(), otherNormals.begin(), otherNormals.end());

    float smallestOverlap = 999999.f;
    sf::Vector2f minTranslationVect = sf::Vector2f(0, 0);

    for (sf::Vector2f n : normals) {
        Projection p1 = projectOnto(n);
        Projection p2 = other.projectOnto(n);

        if (float overlap = p1.overlap(p2); overlap == 0.f) {
            mLastCollision = Collision(false);
            return mLastCollision;
        } else {
            if (overlap < smallestOverlap) {
                smallestOverlap = overlap;

                // check if normal is pointing towards or away other
                // this must be done in the case of parallel vectors
                if (Vector2Math::dot(getMidpoint() - other.getMidpoint(), n) < 0) {
                    n *= -1.f;
                }

                minTranslationVect = n * smallestOverlap;
            }
        }
    }

    mLastCollision = Collision(minTranslationVect);
    return mLastCollision;
}

Collision CollisionPolygon::getLastCollision() const {
    return mLastCollision;
}

std::vector<sf::Vector2f> CollisionPolygon::getNormals() const {
    std::vector<sf::Vector2f> normals;
    for (uint i=0; i<mVertexArray.getVertexCount(); i++) {
        sf::Vector2f v1 = getTransform().transformPoint(Vector2Math::toVector2f(mVertexArray[i]));
        // gets next index (loops to 0 on overflow)
        uint nextIdx = (i + 1 == mVertexArray.getVertexCount() ? 0 : i + 1);
        sf::Vector2f v2 = getTransform().transformPoint(Vector2Math::toVector2f(mVertexArray[nextIdx]));

        sf::Vector2f side = v2 - v1;
        normals.push_back(Vector2Math::normalize(Vector2Math::normal(side)));
    }
    return normals;
}

Projection CollisionPolygon::projectOnto(const sf::Vector2f &axis) const {
    sf::Vector2f nAxis = Vector2Math::normalize(axis);

    float min = Vector2Math::dot(getTransform().transformPoint(Vector2Math::toVector2f(mVertexArray[0])), nAxis);
    float max = min;

    for (uint i=1; i<mVertexArray.getVertexCount(); i++) {
        sf::Vector2f v = getTransform().transformPoint(Vector2Math::toVector2f(mVertexArray[i]));
        float dot = Vector2Math::dot(v, nAxis);
        if (dot < min) {
            min = dot;
        } else if (dot > max) {
            max = dot;
        }
    }

    return Projection(min, max);
}

void CollisionPolygon::clear() {
    mVertexArray.clear();
}

void CollisionPolygon::resize(std::size_t size) {
    mVertexArray.resize(size);
}

void CollisionPolygon::setPrimitiveType(sf::PrimitiveType type) { 
    mVertexArray.setPrimitiveType(type); 
}

std::size_t CollisionPolygon::getVertexCount() {
    return mVertexArray.getVertexCount();
}

} // shoe

// Collision operators
bool operator == (const shoe::Collision &a, const bool &b) { return a.hit == b; }
bool operator == (const bool &b, const shoe::Collision &a) { return a.hit == b; }
bool operator != (const shoe::Collision &a, const bool &b) { return !(a == b); }
bool operator != (const bool &b, const shoe::Collision &a) { return !(a == b); }
bool operator && (const shoe::Collision &a, const bool &b) { return a.hit && b; }
bool operator && (const bool &b, const shoe::Collision &a) { return a.hit && b; }
bool operator || (const shoe::Collision &a, const bool &b) { return a.hit || b; }
bool operator || (const bool &b, const shoe::Collision &a) { return a.hit || b; }