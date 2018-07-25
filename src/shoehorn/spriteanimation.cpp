/*
 * sprite animation
 * 
 * Josh Chandler
*/

#include "include/gameobject.hpp"
#include "include/spriteanimation.hpp"


namespace shoe {
    
SpriteAnimation::SpriteAnimation(GameObject *target) 
: mTargetObject {target}
, mPosition {0}
, mPlaying {false}
{
    
}

void SpriteAnimation::clear() {
    mKeyframes.clear();
}

void SpriteAnimation::addKeyframe(uint x, uint y, uint w, uint h, uint weight) {
    addKeyframe(Keyframe(x, y, w, h, weight));
}

void SpriteAnimation::addKeyframe(Keyframe keyframe) {
    mKeyframes.push_back(keyframe);
}

void SpriteAnimation::play(sf::Time duration) {
    mPlaying = true;
    mLength = duration;
}

void SpriteAnimation::pause() {
    mPlaying = false;
}

void SpriteAnimation::goTo(float percent) {
    mPosition = percent;
}

void SpriteAnimation::update(const sf::Time &dTime) {
    if (!mPlaying) return;

    mPosition += dTime/mLength * 100.f;

    if (mPosition > 100.f) {
        mPosition -= 100.f;
    }

    if (mKeyframes.size() != 0) { // placeholder
        if (mPosition < 50) { // placeholder
            mTargetObject->setSpriteTextureRect(mKeyframes[0].rect);
        } else {
            mTargetObject->setSpriteTextureRect(mKeyframes[1].rect);
        }
    }
}

} // shoe
