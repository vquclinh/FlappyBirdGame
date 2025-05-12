#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

class SettingsScreen {
public:
    SettingsScreen(sf::RenderWindow& win);
    ~SettingsScreen(); // Destructor

    void handleEvent(sf::Event& event, ScreenState& state);
    void draw();
    void update();

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text title;

    sf::RectangleShape backButton;
    sf::Text backText;
};
