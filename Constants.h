#pragma once

#include <SFML/Graphics.hpp>

enum ScreenState {
    MAINMENU,
    GAMEPLAY,
    SETTINGS,
    ABOUT
};

const int Screen_h = 900;
const int Screen_w = 1600;

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

extern std::string playerName;
