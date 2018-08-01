/*
 * collision polygon
 *
 * uses SAT to check for collisions with other polygons
 *  
 * Josh Chandler
*/

#pragma once

#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

namespace shoe {

struct Projection {
    Projection(float minn, float maxx)
    : min {minn}
    , max {maxx}
    {};

    float overlap(const Projection &p) const {
        // this calculates the length of the overlap
        return std::max(0.f, std::min(max, p.max) - std::max(min, p.min));
    };

    float min;
    float max;
};

struct Collision {
    Collision() {
        MTA = sf::Vector2f(0, 0);
        hit = false;
    }

    Collision(const bool &_hit) {
        hit = _hit;
    }

    Collision(const sf::Vector2f &mta) {
        MTA = mta;
        hit = true;
    }

    sf::Vector2f MTA;
    bool hit;
};
    
class CollisionPolygon : public sf::Drawable, public sf::Transformable {
public:

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void loadPointsFromVertexArray(const sf::VertexArray &verts);
    void makeIntoRegularShape(uint sides, uint radius);

    sf::Vector2f getMidpoint() const;

    std::vector<sf::Vector2f> getNormals() const;
    Projection projectOnto(const sf::Vector2f &axis) const;

    Collision collidesWith(const CollisionPolygon &other);
    Collision getLastCollision() const;

    void clear();
    void resize(std::size_t size);
    void setPrimitiveType(sf::PrimitiveType type);
    std::size_t getVertexCount();

    sf::Vertex& operator[](std::size_t size) {
        return mVertexArray[size];
    }
protected:
    sf::VertexArray mVertexArray;
    Collision mLastCollision;
};

} // shoe

// Collision operators
bool operator == (const shoe::Collision &a, const bool &b); 
bool operator == (const bool &b, const shoe::Collision &a); 
bool operator != (const shoe::Collision &a, const bool &b); 
bool operator != (const bool &b, const shoe::Collision &a);
bool operator && (const shoe::Collision &a, const bool &b); 
bool operator && (const bool &b, const shoe::Collision &a); 
bool operator || (const shoe::Collision &a, const bool &b); 
bool operator || (const bool &b, const shoe::Collision &a); 
