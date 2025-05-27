#include "MenuScreen.h"

MenuScreen::MenuScreen(sf::RenderWindow& win) : window(win), textBox(sf::Vector2f(0, 0), sf::Vector2f(50, 20), &font, 28){
    font.loadFromFile("Assets/Fonts/LilitaOne-Regular.ttf");
    init();
}

void MenuScreen::init() {
    // Load textures
    backgroundTexture.loadFromFile("Assets/Images/background.png");
    backgroundSprite1.setTexture(backgroundTexture);
    backgroundSprite2.setTexture(backgroundTexture);
    backgroundSprite3.setTexture(backgroundTexture);

    // Scale để ảnh vừa với cửa sổ
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;

    backgroundSprite1.setScale(scaleX, scaleY);
    backgroundSprite2.setScale(scaleX, scaleY);
    backgroundSprite3.setScale(scaleX, scaleY);

    // Đặt vị trí ban đầu cho Sprite2 và Sprite3
    backgroundSprite2.setPosition(windowSize.x, 0);
    backgroundSprite3.setPosition(windowSize.x * 2, 0);

    // Text và button
    float windowWidth = windowSize.x;
    float centerX = windowWidth / 2;

    titleText.setFont(font);
    titleText.setString("Flappy Bird");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color(198, 23, 133, 225));
    titleText.setPosition(centerX - titleText.getGlobalBounds().width / 2, 50);

    nameLabel.setFont(font);
    nameLabel.setString("Enter Name:");
    nameLabel.setCharacterSize(28);
    nameLabel.setPosition(centerX - nameLabel.getGlobalBounds().width / 2 - 75, 150);
    nameLabel.setFillColor(sf::Color(105, 129, 136, 225));

    nameInput.setFont(font);
    nameInput.setCharacterSize(28);
    nameInput.setFillColor(sf::Color(197, 192, 10, 225));
    nameInput.setPosition(centerX - nameInput.getGlobalBounds().width / 2, 190);

    playButton.setSize({ 200, 50 });
    playButton.setPosition(centerX - 100, 260);
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(24);
    playText.setPosition(centerX - playText.getGlobalBounds().width / 2, 270);

    settingsButton.setSize({ 200, 50 });
    settingsButton.setPosition(centerX - 100, 330);
    settingsText.setFont(font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(24);
    settingsText.setPosition(centerX - settingsText.getGlobalBounds().width / 2, 340);

    aboutButton.setSize({ 200, 50 });
    aboutButton.setPosition(centerX - 100, 400);
    aboutText.setFont(font);
    aboutText.setString("About");
    aboutText.setCharacterSize(24);
    aboutText.setPosition(centerX - aboutText.getGlobalBounds().width / 2, 410);

    // Đặt lại vị trí của textBox 
    sf::Vector2f nameLabelPos = nameLabel.getPosition();
    float textBoxWidth = 150;
    float textBoxHeight = 40;
    sf::Vector2f textBoxPos(
        nameLabelPos.x + 168,
        nameLabelPos.y
    );
    textBox.setPosition(textBoxPos);
    textBox.setSize(sf::Vector2f(textBoxWidth, textBoxHeight));
}

void MenuScreen::handleEvent(sf::Event& event, ScreenState& state) {
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
        if (playButton.getGlobalBounds().contains(mouse)) {
            state = ScreenState::GAMEPLAY;
        }
    }
    textBox.handleEvent(event);
}

void MenuScreen::update() {
    sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);

    float layer4Speed = 200.0f;
    float deltaTime = 1.0f / 60.0f; // Giả sử 60 FPS
    float layer4Width = backgroundSprite1.getGlobalBounds().width;

    backgroundSprite1.move(-layer4Speed * deltaTime, 0);
    backgroundSprite2.move(-layer4Speed * deltaTime, 0);
    backgroundSprite3.move(-layer4Speed * deltaTime, 0);

    // Đặt lại vị trí khi sprite ra khỏi màn hình
    if (backgroundSprite1.getPosition().x <= -layer4Width) {
        backgroundSprite1.setPosition(backgroundSprite3.getPosition().x + layer4Width, 0);
    }
    if (backgroundSprite2.getPosition().x <= -layer4Width) {
        backgroundSprite2.setPosition(backgroundSprite1.getPosition().x + layer4Width, 0);
    }
    if (backgroundSprite3.getPosition().x <= -layer4Width) {
        backgroundSprite3.setPosition(backgroundSprite2.getPosition().x + layer4Width, 0);
    }

    isPlayHovered = playButton.getGlobalBounds().contains(mouse);
    isSettingsHovered = settingsButton.getGlobalBounds().contains(mouse);
    isAboutHovered = aboutButton.getGlobalBounds().contains(mouse);

    playButton.setFillColor(isPlayHovered ? sf::Color(40, 203, 114, 100) : sf::Color(40, 203, 114, 225));
    settingsButton.setFillColor(isSettingsHovered ? sf::Color(28, 83, 248, 100) : sf::Color(28, 83, 248, 225));
    aboutButton.setFillColor(isAboutHovered ? sf::Color(222, 209, 38, 100) : sf::Color(222, 209, 38, 225));
    
    textBox.update(deltaTime);
}

void MenuScreen::draw() {
    window.draw(backgroundSprite1);
    window.draw(backgroundSprite2);
    window.draw(backgroundSprite3);

    window.draw(titleText);
    window.draw(nameLabel);
    window.draw(nameInput);

    window.draw(playButton);
    window.draw(playText);
    window.draw(settingsButton);
    window.draw(settingsText);
    window.draw(aboutButton);
    window.draw(aboutText);

    textBox.draw(window);
}

std::string MenuScreen::getPlayerName() const {
    return textBox.getText();
}