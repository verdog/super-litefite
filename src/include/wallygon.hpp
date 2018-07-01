/*
 * wallygon
 * 
 * Josh Chandler
*/

#include <SFML/Graphics.hpp>

namespace shoe {
    class GameObject;
    class CollisionPolygon;
}

class Wallygon : public sf::VertexArray {
public:
    Wallygon();
    ~Wallygon();

    void randomize(uint sides, uint radius, sf::Vector2u size);
    void randomize(uint sided, uint radius, uint maxX, uint maxY);

    void setPosition(sf::Vector2f position);

    sf::Vector2f collidesWith(const shoe::GameObject &other);

    shoe::CollisionPolygon collisionPolygon();

    int mRot;
    int mRad;
    sf::Vector2f mPosition;
    std::unique_ptr<shoe::CollisionPolygon> mCPolygon;
private:
};