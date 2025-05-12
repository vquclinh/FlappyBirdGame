#include "AboutScreen.h"

AboutScreen::AboutScreen(sf::RenderWindow& win) : window(win) {
    font.loadFromFile("assets/fonts/LilitaOne-Regular.ttf");

    title.setFont(font);
    title.setString("About");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(320, 80);

    info.setFont(font);
    info.setCharacterSize(22);
    info.setFillColor(sf::Color::White);
    info.setString("Flappy Bird clone using SFML\nBy LNKH Team\nAPCS K24 - UoS");
    info.setPosition(200, 180);

    backButton.setSize({ 150, 50 });
    backButton.setFillColor(sf::Color::Red);
    backButton.setPosition(325, 400);

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(370, 410);
}

AboutScreen::~AboutScreen() {
    // Nothing to clean up manually
}

void AboutScreen::handleEvent(sf::Event& event, ScreenState& state) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));

        if (backButton.getGlobalBounds().contains(mouse)) {
            state = ScreenState::MAINMENU;
        }
    }
}

void AboutScreen::update() {
    sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);
}

void AboutScreen::draw() {
    window.draw(title);
    window.draw(info);
    window.draw(backButton);
    window.draw(backText);
}
