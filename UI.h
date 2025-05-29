#pragma once
#include <SFML/Graphics.hpp>
#include "MenuScreen.h"
#include "SettingsScreen.h"
#include "AboutScreen.h"
#include "Constants.h"
#include "PlayScreen.h"

class UI {
public:
    UI();
    ~UI();
    void run();

private:
    sf::RenderWindow window;
    ScreenState currentState;

    MenuScreen menu;
    SettingsScreen settings;
    AboutScreen about;
    PlayGame play;
    
    AudioSystem audio;
    void processEvents();
    void update(float dt);
    void render();

    sf::Clock clock;
    sf::Image icon;
};
