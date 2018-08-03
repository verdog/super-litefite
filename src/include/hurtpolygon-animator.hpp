/*
 * HurtPolygon Animator
 * 
 * Josh Chandler
*/

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

class HurtPolygon;

class HurtPolygonAnimator : sf::Drawable{
public:
    HurtPolygonAnimator();

    void insert(std::shared_ptr<HurtPolygon> hp);
    void clear();
    void setPosition(sf::Vector2f position);
    void rotate(float angle);
    void setRotation(float angle);

    void addVulnerability(const shoe::GameObject &object);
    void removeVulnerability(const shoe::GameObject &object);

    bool canHurt(const shoe::GameObject &object);

    void play(const sf::Time &duration, bool loop = false, uint cycles = 1);
    void stop();
    
    void update(const sf::Time &dTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    std::vector<std::shared_ptr<HurtPolygon>> mFrames;
    HurtPolygon *mCurrentFrame;

    bool mPlaying;
    bool mLooping;
    uint mElapsedCycles;
    uint mEndCycles;
    sf::Time mCurrentTime;
    sf::Time mEndTime;
};
