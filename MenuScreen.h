#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"

class MenuScreen {
public:
    MenuScreen(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, ScreenState& state);
    void draw();
    void update();
    std::string getPlayerName() const;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText, nameLabel, nameInput;
    sf::RectangleShape playButton, settingsButton, aboutButton;
    sf::Text playText, settingsText, aboutText;

    std::string playerName;
    bool typing = false;

    void init();
};
