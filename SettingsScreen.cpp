#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(sf::RenderWindow& win) : window(win) {
    font.loadFromFile("assets/fonts/LilitaOne-Regular.ttf");

    title.setFont(font);
    title.setString("Settings");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(280, 100);

    backButton.setSize({ 150, 50 });
    backButton.setFillColor(sf::Color::Red);
    backButton.setPosition(325, 400);

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(370, 410);
}

SettingsScreen::~SettingsScreen() {
    // Nothing to clean up manually
}

void SettingsScreen::handleEvent(sf::Event& event, ScreenState& state) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));

        if (backButton.getGlobalBounds().contains(mouse)) {
            state = ScreenState::MAINMENU;
        }
    }
}

void SettingsScreen::update() {
    sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);
}

void SettingsScreen::draw() {
    window.draw(title);
    window.draw(backButton);
    window.draw(backText);
}
