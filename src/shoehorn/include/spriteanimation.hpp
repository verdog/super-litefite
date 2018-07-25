/*
 * sprite animation
 * 
 * Josh Chandler
*/

#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace shoe {
    
class GameObject;

struct Keyframe {
    Keyframe(uint x, uint y, uint w, uint h, uint _weight) {
        rect = sf::IntRect(x, y, w, h);
        weight = _weight;
    }

    sf::IntRect rect;
    uint weight;
};

class SpriteAnimation {
public:
    SpriteAnimation(GameObject *target);

    void clear();
    void addKeyframe(uint x, uint y, uint w, uint h, uint weight);
    void addKeyframe(Keyframe keyframe);
    void play(sf::Time duration);
    void pause();
    void goTo(float percent);

    void update(const sf::Time &dTime);

private:
    GameObject *mTargetObject;
    std::vector<Keyframe> mKeyframes;
    sf::Time mLength;
    float mPosition;
    bool mPlaying;
};

} // shoe
