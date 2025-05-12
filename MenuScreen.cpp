#include "MenuScreen.h"

MenuScreen::MenuScreen(sf::RenderWindow& win) : window(win) {
    font.loadFromFile("Assets/Fonts/LilitaOne-Regular.ttf");
    init();
}

void MenuScreen::init() {
    titleText.setFont(font);
    titleText.setString("Flappy Bird");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(220, 50);

    nameLabel.setFont(font);
    nameLabel.setString("Enter Name:");
    nameLabel.setCharacterSize(28);
    nameLabel.setPosition(220, 150);

    nameInput.setFont(font);
    nameInput.setCharacterSize(28);
    nameInput.setPosition(220, 190);
    nameInput.setFillColor(sf::Color::White);

    playButton.setSize({ 200, 50 });
    playButton.setFillColor(sf::Color::Green);
    playButton.setPosition(300, 260);
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(24);
    playText.setPosition(370, 270);

    settingsButton.setSize({ 200, 50 });
    settingsButton.setFillColor(sf::Color::Blue);
    settingsButton.setPosition(300, 330);
    settingsText.setFont(font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(24);
    settingsText.setPosition(340, 340);

    aboutButton.setSize({ 200, 50 });
    aboutButton.setFillColor(sf::Color::Cyan);
    aboutButton.setPosition(300, 400);
    aboutText.setFont(font);
    aboutText.setString("About");
    aboutText.setCharacterSize(24);
    aboutText.setPosition(360, 410);
}

void MenuScreen::handleEvent(sf::Event& event, ScreenState& state) {
    if (event.type == sf::Event::TextEntered && typing) {
        if (event.text.unicode == 8 && !playerName.empty()) {
            playerName.pop_back();
        }
        else if (event.text.unicode < 128 && playerName.size() < 15 && event.text.unicode != 8) {
            playerName += static_cast<char>(event.text.unicode);
        }
        nameInput.setString(playerName);
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));

        if (nameInput.getGlobalBounds().contains(mouse)) typing = true;
        else typing = false;

        if (playButton.getGlobalBounds().contains(mouse)) {
            if (!playerName.empty()) state = ScreenState::GAMEPLAY;
        }
        if (settingsButton.getGlobalBounds().contains(mouse)) {
            state = ScreenState::SETTINGS;
        }
        if (aboutButton.getGlobalBounds().contains(mouse)) {
            state = ScreenState::ABOUT;
        }
    }
}

void MenuScreen::draw() {
    window.draw(titleText);
    window.draw(nameLabel);
    window.draw(nameInput);

    window.draw(playButton);
    window.draw(playText);
    window.draw(settingsButton);
    window.draw(settingsText);
    window.draw(aboutButton);
    window.draw(aboutText);
}

void MenuScreen::update() {
    sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);
}


std::string MenuScreen::getPlayerName() const {
    return playerName;
}
