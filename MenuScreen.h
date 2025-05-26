#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"
#include "TextBox.h"

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

    bool typing = false;

    // Background image
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite1;
    sf::Sprite backgroundSprite2;
    sf::Sprite backgroundSprite3;

    float cloudX = 0.0f, fenceX = 0.0f;

    bool isPlayHovered = false;
    bool isSettingsHovered = false;
    bool isAboutHovered = false;

    TextBox textBox;

    void init();
};
