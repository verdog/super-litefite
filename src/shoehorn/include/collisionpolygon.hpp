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
    
class CollisionPolygon : public sf::VertexArray {
public:
    CollisionPolygon();
    ~CollisionPolygon();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void loadPointsFromVertexArray(const sf::VertexArray &verts);

    void setPosition(sf::Vector2f position);

    sf::Vector2f getMidpoint() const;

    sf::Transform transform();
    void setTransform(sf::Transform transform);

    std::vector<sf::Vector2f> getNormals() const;
    Projection projectOnto(const sf::Vector2f &axis) const;
    sf::Vector2f toVector2f(const sf::Vertex &v) const;

    sf::Vector2f collidesWith(const CollisionPolygon &other);
private:
    sf::Vector2f mPosition;
    sf::Transform mTransform;
};

} // shoe
