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

CollisionPolygon::CollisionPolygon() {
    //
}

CollisionPolygon::~CollisionPolygon() {
    //
}

void CollisionPolygon::readPointsFromVertexArray(const sf::VertexArray &verts) {
    clear();
    resize(verts.getVertexCount());
    setPrimitiveType(sf::PrimitiveType::LineStrip);

    for (uint i = 0; i < getVertexCount(); i++) {
        (*this)[i] = verts[i];
    }
}

void CollisionPolygon::setPosition(sf::Vector2f position) {
    sf::Transform newTransform;
    newTransform.translate(position);
    mTransform = newTransform;
    mPosition = position;
}

sf::Transform CollisionPolygon::transform() {
    return mTransform;
}

void CollisionPolygon::setTransform(sf::Transform transform) {
    mTransform = transform;
}

// sf::Vector2f CollisionPolygon::collidesWith(const CollisionPolygon &other) {
//     //
//     return sf::Vector2f(0,0);
// }

bool CollisionPolygon::collidesWith(const CollisionPolygon &other) {
    std::vector<sf::Vector2f> normals = getNormals();
    std::vector<sf::Vector2f> otherNormals = other.getNormals();
    normals.reserve(otherNormals.size());
    normals.insert(normals.end(), otherNormals.begin(), otherNormals.end());

    for (sf::Vector2f n : normals) {
        Projection p1 = projectOnto(n);
        Projection p2 = other.projectOnto(n);

        if (!p1.overlaps(p2)) {
            return false;
        }
    }

    return true;
}

std::vector<sf::Vector2f> CollisionPolygon::getNormals() const {
    std::vector<sf::Vector2f> normals;
    for (uint i=0; i<getVertexCount(); i++) {
        sf::Vector2f v1 = toVector2f((*this)[i]);
        // gets next index (loops to 0 on overflow)
        uint nextIdx = (i + 1 == getVertexCount() ? 0 : i + 1);
        sf::Vector2f v2 = toVector2f((*this)[nextIdx]);

        sf::Vector2f side = v2 - v1;
        normals.push_back(Vector2Math::normalize(Vector2Math::normal(side)));
    }
    return normals;
}

Projection CollisionPolygon::projectOnto(const sf::Vector2f &axis) const {
    sf::Vector2f nAxis = Vector2Math::normalize(axis);

    float min = Vector2Math::dot(mTransform.transformPoint(toVector2f((*this)[0])), nAxis);
    float max = min;

    for (uint i=1; i<getVertexCount(); i++) {
        sf::Vector2f v = mTransform.transformPoint(toVector2f((*this)[i]));
        float dot = Vector2Math::dot(v, nAxis);
        if (dot < min) {
            min = dot;
        } else if (dot > max) {
            max = dot;
        }
    }

    return Projection(min, max);
}

sf::Vector2f CollisionPolygon::toVector2f(const sf::Vertex &v) const {
    return sf::Vector2f(v.position.x, v.position.y);
}

} // shoe
