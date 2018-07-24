/*
 * sprite animator
 * 
 * Josh Chandler
*/

#include "include/gameobject.hpp"
#include "include/spriteanimator.hpp"


namespace shoe {
    
SpriteAnimator::SpriteAnimator(GameObject *target) 
: mTargetObject {target}
, mPosition {0}
, mPlaying {false}
{
    
}

void SpriteAnimator::clear() {
    mKeyframes.clear();
}

void SpriteAnimator::addKeyframe(uint x, uint y, uint w, uint h, uint weight) {
    addKeyframe(Keyframe(x, y, w, h, weight));
}

void SpriteAnimator::addKeyframe(Keyframe keyframe) {
    mKeyframes.push_back(keyframe);
}

void SpriteAnimator::play(sf::Time duration) {
    mPlaying = true;
    mLength = duration;
}

void SpriteAnimator::pause() {
    mPlaying = false;
}

void SpriteAnimator::goTo(float percent) {
    mPosition = percent;
}

void SpriteAnimator::update(const sf::Time &dTime) {
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
