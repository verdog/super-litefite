/*
 * collision polygon
 *
 * uses SAT to check for collisions with other polygons
 *  
 * Josh Chandler
*/

#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

namespace shoe {

struct Projection {
    Projection(float minn, float maxx)
    : min {minn}
    , max {maxx}
    {};

    bool overlaps(const Projection &p) {
        return 
            (max > p.min) &&
            (min < p.max)
            ;
    };

    float min;
    float max;
};
    
class CollisionPolygon : public sf::VertexArray {
public:
    CollisionPolygon();
    ~CollisionPolygon();

    void readPointsFromVertexArray(const sf::VertexArray &verts);

    void setPosition(sf::Vector2f position);

    sf::Transform transform();
    void setTransform(sf::Transform transform);

    std::vector<sf::Vector2f> getNormals() const;
    Projection projectOnto(const sf::Vector2f &axis) const;
    sf::Vector2f toVector2f(const sf::Vertex &v) const;

    // sf::Vector2f collidesWith(const CollisionPolygon &other);
    bool collidesWith(const CollisionPolygon &other);
private:
    sf::Vector2f mPosition;
    sf::Transform mTransform;
};

} // shoe
