/*
 * wallygon
 * 
 * Josh Chandler
*/

#include <SFML/Graphics.hpp>

namespace shoe {
    class GameState;
    class GameObject;
    class CollisionPolygon;
}

class Wallygon : public shoe::GameObject {
public:
    Wallygon(shoe::GameState *state);
    ~Wallygon();

    void randomize(uint sides, uint radius, sf::Vector2u size);
    void randomize(uint sided, uint radius, uint maxX, uint maxY);

    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f vector);

    sf::Vector2f collidesWith(const shoe::GameObject &other);

    shoe::CollisionPolygon collisionPolygon();

    sf::VertexArray getVertices() {
        return mVertices;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    int mRad;
    sf::VertexArray mVertices;
};