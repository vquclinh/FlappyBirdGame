#pragma once

#include <SFML/Graphics.hpp>

enum ScreenState {
    MAINMENU,
    GAMEPLAY,
    SETTINGS,
    ABOUT
};

const int Screen_w = 480;
const int Screen_h = 720;

const int game_w = 480;
const int game_h = 800;

const int offsetX = (Screen_w - game_w) / 2;

extern std::string playerName;
