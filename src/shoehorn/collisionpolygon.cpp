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

sf::Vector2f CollisionPolygon::collidesWith(const CollisionPolygon &other) {
    std::vector<sf::Vector2f> normals = getNormals();
    std::vector<sf::Vector2f> otherNormals = other.getNormals();

    float smallestOverlap = 999999.f;
    sf::Vector2f minTranslationVect = sf::Vector2f(0, 0);

    // two seperate loops are needed to provide the correct MTV
    // this function must return the MTV that would push the object calling it (not other)

    for (sf::Vector2f n : normals) {
        Projection p1 = projectOnto(n);
        Projection p2 = other.projectOnto(n);

        if (float overlap = p1.overlap(p2); overlap == 0.f) {
            return sf::Vector2f(0, 0);
        } else {
            if (overlap < smallestOverlap) {
                smallestOverlap = overlap;
                std::cout << "NEW SMALL (my normals): ";
                // the normal is pointing outwards, but we should "move" inwards
                n = -n;
                std::cout << n.x << ", " << n.y << ", " << overlap << ", " << smallestOverlap << std::endl;
                minTranslationVect = n * smallestOverlap;
            }
        }
    }

    for (sf::Vector2f n : otherNormals) {
        Projection p1 = projectOnto(n);
        Projection p2 = other.projectOnto(n);

        if (float overlap = p1.overlap(p2); overlap == 0.f) {
            return sf::Vector2f(0, 0);
        } else {
            if (overlap < smallestOverlap) {
                smallestOverlap = overlap;
                std::cout << "NEW SMALL (other normals): ";
                std::cout << n.x << ", " << n.y << ", " << overlap << ", " << smallestOverlap << std::endl;
                minTranslationVect = n * smallestOverlap;
            }
        }
    }

    return minTranslationVect;
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
