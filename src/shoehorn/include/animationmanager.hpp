/*
 * animation manager
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>
#include <string>

#include <SFML/System.hpp>

#include "objectmanager.hpp"
#include "spriteanimation.hpp"

namespace shoe {

class AnimationManager : public ObjectManager<SpriteAnimation> {
public:
    void play(const std::string &name, const sf::Time &duration);
    void pause(const std::string &name);
    void update(const sf::Time &dTime);
};
    
} // shoe
