/*
 * animation manager
 * 
 * Josh Chandler
*/

#include "include/animationmanager.hpp"

namespace shoe {

void AnimationManager::play(const std::string &name, const sf::Time &duration) {
    get(name).play(duration);
}

void AnimationManager::pause(const std::string &name) {
    get(name).pause();
}

void AnimationManager::update(const sf::Time &dTime) {
    for (std::pair<const std::string, SpriteAnimation> &p : mMap) {
        p.second.update(dTime);
    }
}

} // shoe
