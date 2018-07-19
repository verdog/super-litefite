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
    struct Collision;
}

class Wallygon : public shoe::GameObject {
public:
    Wallygon(shoe::GameState *state);
    ~Wallygon();

    void randomize(uint sides, uint radius, sf::Vector2u size);
    void randomize(uint sided, uint radius, uint maxX, uint maxY);

    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f vector);

    shoe::Collision collidesWith(const shoe::GameObject &other);

    shoe::CollisionPolygon& getCollisionPolygon();

    sf::VertexArray getVertices() {
        return mVertices;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    int mRad;
    sf::VertexArray mVertices;
};