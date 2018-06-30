/*
 * fps.hpp
 * 
 * FPS counter
 * Josh Chandler
*/

#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

namespace shoe {

class FpsCounter : public sf::Drawable {
public:
    FpsCounter() {
        if (!mFont.loadFromFile("./resources/fonts/NotoMono-Regular.ttf")) {
            std::cout << "Failed to find font at ./resources/fonts/NotoMono-Regular.ttf" << std::endl;
            std::cout << "Failed to load font!" << std::endl;
        }

        mText.setFont(mFont);
        mText.setCharacterSize(32);
        mText.setFillColor(sf::Color::Yellow);
        mText.setString("...");
        mText.setPosition(0, 0);
        
        mClock.restart();

        mFrames = 0;
        mFrames_total = 0;
    };

    ~FpsCounter() = default;

    void tick() {
        mFrames++;
        mFrames_total++;
        // update every x seconds                   x
        if (mClock.getElapsedTime().asSeconds() > 0.1) {
            sf::Time elapsed = mClock.restart();
            mText.setString(std::to_string(
                (float)mFrames/(float)elapsed.asSeconds()
            ));
            mText.setString(mText.getString() + "\n" + std::to_string(mFrames_total));
            mFrames = 0;
        }
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(mText);
    }

    sf::Font mFont;
    sf::Text mText;
    sf::Clock mClock;
    unsigned int mFrames;
    unsigned int mFrames_total;
};

}