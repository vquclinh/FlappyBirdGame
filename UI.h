#pragma once
#include <SFML/Graphics.hpp>
#include "MenuScreen.h"
#include "SettingsScreen.h"
#include "AboutScreen.h"
#include "Constants.h"


class UI {
public:
    UI();
    void run();

private:
    sf::RenderWindow window;
    ScreenState currentState;

    MenuScreen menu;
    SettingsScreen settings;
    AboutScreen about;

    void processEvents();
    void update();
    void render();
};
