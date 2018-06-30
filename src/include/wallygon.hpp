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

    void randomize(uint sides, uint radius, sf::Vector2u size);
    void randomize(uint sided, uint radius, uint maxX, uint maxY);

    int mRot;
    int mRad;
    sf::Vector2f mPosition;
private:
};