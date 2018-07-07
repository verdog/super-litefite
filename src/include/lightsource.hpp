/*
 * lightsource.hpp
 * 
 * Given a list of walls, calculates a visibility mask.
 * 
 * Josh Chandler
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "../shoehorn/include/gameobject.hpp"

class LightSource : public shoe::GameObject {
public:
    LightSource(shoe::GameState *state, shoe::GameObject *anchor);

    void update(const sf::Time &dTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::VertexArray& makeVisibilityShape(const std::vector<shoe::GameObject*>& obstacles);
private:
    shoe::GameObject *mAnchor;
    sf::VertexArray mShape;
    sf::Color mColor;
};