/*
 * wallygon
 * 
 * Josh Chandler
*/

#include <SFML/Graphics.hpp>

class Wallygon : public sf::VertexArray {
public:
    Wallygon();
    ~Wallygon();

    void randomize(sf::Vector2u size);
    void randomize(uint maxX, uint maxY);

    int mRot;
    sf::Vector2f mPosition;
private:
};