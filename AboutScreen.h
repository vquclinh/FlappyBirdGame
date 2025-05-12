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

    sf::RectangleShape backButton;
    sf::Text backText;
};
