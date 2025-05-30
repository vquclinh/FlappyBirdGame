#pragma once

#include <SFML/Graphics.hpp>
#include "../../UI/Constants.h"

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
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite1;
    sf::Sprite backgroundSprite2;
    sf::Sprite backgroundSprite3;

    bool isBackHovered = false;

    sf::RectangleShape backButton;
    sf::Text backText;
};
