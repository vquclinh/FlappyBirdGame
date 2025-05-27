#include "UI.h"
#include <iostream>

UI::UI()
    : window(sf::VideoMode(Screen_w, Screen_h), "Flappy Bird"),
    currentState(ScreenState::MAINMENU),
    menu(window),
    settings(window),
    about(window),
    play(window)
{
    window.setFramerateLimit(60);  // Giới hạn số khung hình
    
    audio.Init();
}

void UI::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void UI::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        switch (currentState) {
        case ScreenState::MAINMENU:
            menu.handleEvent(event, currentState);
            break;
        case ScreenState::SETTINGS:
            settings.handleEvent(event, currentState);
            break;
        case ScreenState::ABOUT:
            about.handleEvent(event, currentState);
        case ScreenState::GAMEPLAY:
            play.handleInput(event, currentState);
            break;
        }
    }
}

void UI::update(float dt) {
    audio.Update();
    switch (currentState) {
    case ScreenState::MAINMENU:
        menu.update();
        break;
    case ScreenState::SETTINGS:
        settings.update();
        break;
    case ScreenState::ABOUT:
        about.update();
        break;
    case ScreenState::GAMEPLAY:
        play.update(dt);
        break;
    }
}

void UI::render() {
    window.clear();

    switch (currentState) {
    case ScreenState::MAINMENU:
        menu.draw();
        break;
    case ScreenState::SETTINGS:
        settings.draw();
        break;
    case ScreenState::ABOUT:
        about.draw();
        break;
    case ScreenState::GAMEPLAY:
        play.render();
        break;
    }

    window.display();
}

UI::~UI() {
    audio.Unload();
}