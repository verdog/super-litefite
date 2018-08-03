/*
 * HurtPolygon Animator
 * 
 * Josh Chandler
*/

#include "include/hurtpolygon.hpp"
#include "include/hurtpolygon-animator.hpp"

HurtPolygonAnimator::HurtPolygonAnimator() 
: mCurrentFrame { nullptr }
, mPlaying { false }
, mLooping { false }
, mElapsedCycles { 0 }
, mEndCycles { 0 }
{
    
}

void HurtPolygonAnimator::insert(std::shared_ptr<HurtPolygon> hp) {
    mFrames.push_back(hp);
}

void HurtPolygonAnimator::clear() {
    mFrames.clear();
}

void HurtPolygonAnimator::setPosition(sf::Vector2f position) {
    for (auto h : mFrames) {
        h->setPosition(position);
    }
}

void HurtPolygonAnimator::rotate(float angle) {
    for (auto h : mFrames) {
        h->rotate(angle);
    }
}

void HurtPolygonAnimator::setRotation(float angle) {
    for (auto h : mFrames) {
        h->setRotation(angle);
    }
}

void HurtPolygonAnimator::addVulnerability(const shoe::GameObject &object) {
    for (auto hp : mFrames) {
        hp->addVulnerability(object);
    }
}

void HurtPolygonAnimator::removeVulnerability(const shoe::GameObject &object) {
    for (auto hp : mFrames) {
        hp->removeVulnerability(object);
    }
}

bool HurtPolygonAnimator::canHurt(const shoe::GameObject &object) {
    for (auto hp : mFrames) {
        if (hp->canHurt(object)) {
            return true;
        }
    }
    return false;
}

void HurtPolygonAnimator::play(const sf::Time &duration, bool loop, uint cycles) {
    std::cout << "Playing animation...\n"; 
    mCurrentTime = sf::seconds(0);
    mPlaying = true;
    mElapsedCycles = 0;

    mEndTime = duration;
    mLooping = loop;
    mEndCycles = cycles;

    if (mFrames.size() > 0) {
        mCurrentFrame = mFrames[0].get();
    } else {
        std::cerr << "ERROR: Tried to play an animation with no frames!\n";
    }
}

void HurtPolygonAnimator::stop() {
    mPlaying = false;
    mCurrentFrame = nullptr;
}

void HurtPolygonAnimator::update(const sf::Time &dTime) {
    if (mPlaying) {
        // determine current frame
        mCurrentTime += dTime;

        // check for an animation loop
        if (mCurrentTime >= mEndTime) {
            if (!mLooping && ++mElapsedCycles >= mEndCycles) { // time to stop
                return stop();
            } else { // just reset the loop
                while (mCurrentTime >= mEndTime) {
                    mCurrentTime -= mEndTime;
                }
            }
        }

        // current frame = floor((percent of animation finished) * number of frames )
        mCurrentFrame = mFrames[ (uint)( mFrames.size() * ( mCurrentTime/mEndTime )) ].get();
        mCurrentFrame->open();
    }

    if (!mCurrentFrame) return; // return if there's no current frame (animation not running)

    for (auto gameObject : mCurrentFrame->getHurtList()) {
        if (canHurt(gameObject) && mCurrentFrame->collidesWith(gameObject.getCollisionPolygon())) {
            std::cout << "did damage!\n";
        }
    }
}

void HurtPolygonAnimator::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!mCurrentFrame) return; // return if there's no current frame (animation not running)
    target.draw(*mCurrentFrame, states);
}