#pragma once

#include <SFML/Graphics.hpp>

enum ScreenState {
    MAINMENU,
    GAMEPLAY,
    SETTINGS,
    ABOUT
};

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

extern std::string playerName;
