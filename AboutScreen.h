#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

class AboutScreen {
public:
    AboutScreen(sf::RenderWindow& win);
    ~AboutScreen(); // Destructor

    void handleEvent(sf::Event& event, ScreenState& state);
    void update();
    void draw();

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text title;
    sf::Text info;


    // Background image
    sf::Texture backgroundTextureLayer1;
    sf::Sprite backgroundSpriteLayer1;
    sf::Texture backgroundTextureLayer2;
    sf::Sprite backgroundSpriteLayer2;
    sf::Texture backgroundTextureLayer3;
    sf::Sprite backgroundSpriteLayer3;
    sf::Texture backgroundTextureLayer4;
    sf::Sprite backgroundSpriteLayer4_1;
    sf::Sprite backgroundSpriteLayer4_2;
    sf::Texture backgroundTextureLayer5;
    sf::Sprite backgroundSpriteLayer5;
    sf::Texture backgroundTextureLayer6;
    sf::Sprite backgroundSpriteLayer6_1;
    sf::Sprite backgroundSpriteLayer6_2;

    float cloudX = 0.0f, fenceX = 0.0f;

    sf::RectangleShape backButton;
    sf::Text backText;
};
