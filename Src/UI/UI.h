#pragma once
#include <SFML/Graphics.hpp>
#include "../Screens/MenuScreen/MenuScreen.h"
#include "../Screens/SettingsScreen/SettingsScreen.h"
#include "../Screens/AboutScreen/AboutScreen.h"
#include "Constants.h"
#include "../Screens/PlayScreen/PlayScreen.h"

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
