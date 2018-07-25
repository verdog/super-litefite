/*
 * sprite animation
 * 
 * Josh Chandler
*/

#include <iostream>

#include "include/gameobject.hpp"
#include "include/spriteanimation.hpp"

namespace shoe {
    
SpriteAnimation::SpriteAnimation(GameObject *target) 
: mTargetObject {target}
, mTotalweight {0}
, mPosition {0}
, mPlaying {false}
{
    
}

void SpriteAnimation::clear() {
    mKeyframes.clear();
    mTotalweight = 0;
}

void SpriteAnimation::addKeyframe(uint x, uint y, uint w, uint h) {
    addKeyframe(Keyframe(x, y, w, h));
}

void SpriteAnimation::addKeyframe(Keyframe keyframe) {
    keyframe.weight = 1;
    mKeyframes.push_back(keyframe);
    mTotalweight += keyframe.weight;
}

void SpriteAnimation::play(sf::Time duration) {
    mPlaying = true;
    mTime = duration;
}

void SpriteAnimation::pause() {
    mPlaying = false;
}

void SpriteAnimation::goTo(float percent) {
    if (percent >= 1.f) {
        float old = percent;
        while (percent >= 1.f) {
            percent /= 100.f;
        }

        std::cout << "SpriteAnimation::goTo : changed " << old << " to " << percent << std::endl;
    }

    mPosition = percent;
}

void SpriteAnimation::update(const sf::Time &dTime) {
    if (!mPlaying) return;

    mPosition += dTime/mTime;

    while (mPosition >= 1.f) {
        mPosition -= 1.f;
    }

    uint frame = mPosition * mKeyframes.size();
    mTargetObject->setSpriteTextureRect(mKeyframes[frame].rect);
}

} // shoe
