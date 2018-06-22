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

    int rot;
private:
};