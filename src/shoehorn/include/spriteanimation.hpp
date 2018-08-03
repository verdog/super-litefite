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
    Keyframe(uint x, uint y, uint w, uint h) {
        rect = sf::IntRect(x, y, w, h);
    }

    sf::IntRect rect;
    uint weight;
};

class SpriteAnimation {
public:
    SpriteAnimation(GameObject &target);

    void clear();
    void addKeyframe(uint x, uint y, uint w, uint h);
    void addKeyframe(Keyframe keyframe);
    void play(sf::Time duration);
    void pause();
    void goTo(float percent);

    void update(const sf::Time &dTime);

private:
    GameObject &mTargetObject;
    std::vector<Keyframe> mKeyframes;
    sf::Time mEndTime;
    uint mTotalweight;
    float mPosition;
    bool mPlaying;
};

} // shoe
