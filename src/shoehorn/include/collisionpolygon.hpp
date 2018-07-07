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
    
class CollisionPolygon : public sf::Drawable, public sf::Transformable {
public:
    CollisionPolygon();
    ~CollisionPolygon();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void loadPointsFromVertexArray(const sf::VertexArray &verts);

    sf::Vector2f getMidpoint() const;

    std::vector<sf::Vector2f> getNormals() const;
    Projection projectOnto(const sf::Vector2f &axis) const;

    sf::Vector2f collidesWith(const CollisionPolygon &other);

    void clear() { mVertexArray.clear(); }
    void resize(std::size_t size) { mVertexArray.resize(size); }
    void setPrimitiveType(sf::PrimitiveType type) { mVertexArray.setPrimitiveType(type); }
    std::size_t getVertexCount() { return mVertexArray.getVertexCount(); }

    sf::Vertex& operator[](std::size_t size) {
        return mVertexArray[size];
    }
private:
    sf::VertexArray mVertexArray;
};

} // shoe
