/*
 * HurtPolygon Animator
 * 
 * Josh Chandler
*/

#include "include/hurtpolygon.hpp"
#include "include/hurtpolygon-animator.hpp"

HurtPolygonAnimator::HurtPolygonAnimator() 
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

void HurtPolygonAnimator::update(const sf::Time &dTime) {
    // incorperate current frame
    for (auto hurtPolygon : mFrames) {
        for (auto gameObject : hurtPolygon->getHurtList()) {
            if (canHurt(gameObject) && hurtPolygon->collidesWith(gameObject.getCollisionPolygon())) {
                std::cout << "did damage!\n";
            }
        }
    }
}

void HurtPolygonAnimator::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // replace with "draw current frame"
    for (auto h : mFrames) {
        target.draw(*h, states);
    }
}