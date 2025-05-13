#include "MenuScreen.h"

MenuScreen::MenuScreen(sf::RenderWindow& win) : window(win) {
    font.loadFromFile("Assets/Fonts/LilitaOne-Regular.ttf");
    init();
}

void MenuScreen::init() {
    // Load textures
    backgroundTextureLayer1.loadFromFile("Assets/Images/layer-1.png");
    backgroundSpriteLayer1.setTexture(backgroundTextureLayer1);
    backgroundTextureLayer2.loadFromFile("Assets/Images/layer-2.png");
    backgroundSpriteLayer2.setTexture(backgroundTextureLayer2);
    backgroundTextureLayer3.loadFromFile("Assets/Images/layer-3.png");
    backgroundSpriteLayer3.setTexture(backgroundTextureLayer3);
    backgroundTextureLayer4.loadFromFile("Assets/Images/layer-4.png");
    backgroundSpriteLayer4_1.setTexture(backgroundTextureLayer4);
    backgroundSpriteLayer4_2.setTexture(backgroundTextureLayer4);
    backgroundTextureLayer5.loadFromFile("Assets/Images/layer-5.png");
    backgroundSpriteLayer5.setTexture(backgroundTextureLayer5);
    backgroundTextureLayer6.loadFromFile("Assets/Images/layer-6.png");
    backgroundSpriteLayer6_1.setTexture(backgroundTextureLayer6);
    backgroundSpriteLayer6_2.setTexture(backgroundTextureLayer6);

    // Scale để ảnh vừa với cửa sổ
    sf::Vector2u textureSize = backgroundTextureLayer1.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;

    backgroundSpriteLayer1.setScale(scaleX, scaleY);
    backgroundSpriteLayer2.setScale(scaleX, scaleY);
    backgroundSpriteLayer3.setScale(scaleX, scaleY);
    backgroundSpriteLayer4_1.setScale(scaleX, scaleY);
    backgroundSpriteLayer4_2.setScale(scaleX, scaleY);
    backgroundSpriteLayer5.setScale(scaleX, scaleY);
    backgroundSpriteLayer6_1.setScale(scaleX, scaleY);
    backgroundSpriteLayer6_2.setScale(scaleX, scaleY);

    // Đặt vị trí cho layer4 (hàng rào) và layer6 (mây) để liền mạch
    backgroundSpriteLayer4_2.setPosition(windowSize.x, 0); // Sprite thứ hai bắt đầu ngay sau sprite đầu tiên
    backgroundSpriteLayer6_2.setPosition(windowSize.x, 0);


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
    nameLabel.setPosition(centerX - nameLabel.getGlobalBounds().width / 2, 150);
    nameLabel.setFillColor(sf::Color(105, 129, 136, 225));

    nameInput.setFont(font);
    nameInput.setCharacterSize(28);
    nameInput.setFillColor(sf::Color(197, 192, 10, 225));
    nameInput.setPosition(centerX - nameInput.getGlobalBounds().width / 2, 190);

    playButton.setSize({ 200, 50 });
    playButton.setFillColor(sf::Color(40, 203, 114, 225));
    playButton.setPosition(centerX - 100, 260);
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(24);
    playText.setPosition(centerX - playText.getGlobalBounds().width / 2, 270);

    settingsButton.setSize({ 200, 50 });
    settingsButton.setFillColor(sf::Color(28, 83, 248, 225));
    settingsButton.setPosition(centerX - 100, 330);
    settingsText.setFont(font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(24);
    settingsText.setPosition(centerX - settingsText.getGlobalBounds().width / 2, 340);

    aboutButton.setSize({ 200, 50 });
    aboutButton.setFillColor(sf::Color(222, 209, 38, 225));
    aboutButton.setPosition(centerX - 100, 400);
    aboutText.setFont(font);
    aboutText.setString("About");
    aboutText.setCharacterSize(24);
    aboutText.setPosition(centerX - aboutText.getGlobalBounds().width / 2, 410);
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

void MenuScreen::update() {
    sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);

    // Di chuyển layer4 (hàng rào) với tốc độ nhanh hơn
    float layer4Speed = 100.0f; // Pixel/giây
    float deltaTime = 1.0f / 60.0f; // Giả sử 60 FPS
    float layer4Width = backgroundSpriteLayer4_1.getGlobalBounds().width;

    backgroundSpriteLayer4_1.move(-layer4Speed * deltaTime, 0);
    backgroundSpriteLayer4_2.move(-layer4Speed * deltaTime, 0);

    // Đặt lại vị trí khi sprite ra khỏi màn hình
    if (backgroundSpriteLayer4_1.getPosition().x <= -layer4Width) {
        backgroundSpriteLayer4_1.setPosition(layer4Width, 0);
    }
    if (backgroundSpriteLayer4_2.getPosition().x <= -layer4Width) {
        backgroundSpriteLayer4_2.setPosition(layer4Width, 0);
    }

    // Di chuyển layer6 (mây) với tốc độ chậm hơn
    float layer6Speed = 30.0f; // Pixel/giây
    float layer6Width = backgroundSpriteLayer6_1.getGlobalBounds().width;

    backgroundSpriteLayer6_1.move(-layer6Speed * deltaTime, 0);
    backgroundSpriteLayer6_2.move(-layer6Speed * deltaTime, 0);

    // Đặt lại vị trí khi sprite ra khỏi màn hình
    if (backgroundSpriteLayer6_1.getPosition().x <= -layer6Width) {
        backgroundSpriteLayer6_1.setPosition(layer6Width, 0);
    }
    if (backgroundSpriteLayer6_2.getPosition().x <= -layer6Width) {
        backgroundSpriteLayer6_2.setPosition(layer6Width, 0);
    }
}

void MenuScreen::draw() {
    window.draw(backgroundSpriteLayer1);
    window.draw(backgroundSpriteLayer2);
    window.draw(backgroundSpriteLayer3);
    window.draw(backgroundSpriteLayer4_1);
    window.draw(backgroundSpriteLayer4_2);
    window.draw(backgroundSpriteLayer5);
    window.draw(backgroundSpriteLayer6_1);
    window.draw(backgroundSpriteLayer6_2);

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

std::string MenuScreen::getPlayerName() const {
    return playerName;
}