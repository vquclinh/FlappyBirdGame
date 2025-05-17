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

    bool isPlayHovered = false;
    bool isSettingsHovered = false;
    bool isAboutHovered = false;

    TextBox textBox;

    void init();
};
