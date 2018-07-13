/*
 * lightsource.hpp
 * 
 * Given a list of walls, calculates a visibility mask.
 * 
 * Josh Chandler
*/

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "../shoehorn/include/gameobject.hpp"

class LightSource : public shoe::GameObject {
public:
    LightSource(shoe::GameState *state, std::shared_ptr<shoe::GameObject> anchor);

    void update(const sf::Time &dTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void setColor(sf::Color color) { mColor = color; }
    sf::Color getColor() const { return mColor; }

    sf::VertexArray& makeVisibilityShape(const std::vector<std::shared_ptr<GameObject>>& obstacles);
    sf::VertexArray getVisibilityShape() const;
private:
    std::shared_ptr<shoe::GameObject> mAnchor;
    sf::VertexArray mShape;
    sf::Color mColor;
};