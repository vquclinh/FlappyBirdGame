#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../../UI/Constants.h"
#include <iostream>

extern bool isMusicOn;
extern sf::Music backgroundMusic;

class SettingsScreen {
public:
    SettingsScreen(sf::RenderWindow& win);
    ~SettingsScreen();

    void handleEvent(sf::Event& event, ScreenState& state);
    void draw();
    void update();

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text title;

    // Background image
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite1;
    sf::Sprite backgroundSprite2;
    sf::Sprite backgroundSprite3;

    float cloudX = 0.0f, fenceX = 0.0f;

    // Nút Back 
    sf::RectangleShape backButton;
    sf::Text backText;
    bool isBackHovered = false;

    // Âm thanh
    sf::RectangleShape soundButton;
    sf::Text soundText;
    bool isSoundHovered = false;
};

class AudioSystem {
private:

public:
    void Init();

    void Update();

    void Unload();
};
