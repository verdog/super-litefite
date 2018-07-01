/*
 * 2d vector math
 * 
 * Some vector stuff
 * 
 * Josh Chandler
*/

#include <cmath>

#include <SFML/Graphics.hpp>

namespace shoe {

class Vector2Math {
public:
    static float magnitude(const sf::Vector2f &v) {
        return std::sqrt(v.x*v.x + v.y*v.y);
    }

    static sf::Vector2f normalize(const sf::Vector2f &v) {
        return v/magnitude(v);
    }

    static float dot(const sf::Vector2f &v, const sf::Vector2f &u) {
        return v.x*u.x + v.y*u.y;
    }

    static sf::Vector2f normal(const sf::Vector2f &v) {
        return sf::Vector2f(v.y, -v.x);
    }

    static sf::Vector2f projection(const sf::Vector2f &v, const sf::Vector2f &axis) {
        return dot(v, normalize(axis)) * axis;
    }
};

} // shoe   