#include "AboutScreen.h"

AboutScreen::AboutScreen(sf::RenderWindow& win) : window(win) {
    font.loadFromFile("Assets/Fonts/LilitaOne-Regular.ttf");

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

    // Text and Button
    float windowWidth = windowSize.x;
    float centerX = windowWidth / 2;

    title.setFont(font);
    title.setString("About");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color(198, 23, 133, 225));
    title.setPosition(centerX - title.getGlobalBounds().width / 2, 50);

    info.setFont(font);
    info.setCharacterSize(22);
    info.setFillColor(sf::Color(238, 29, 52, 225));
    info.setString(
        "We hope you enjoy playing our version of\n"
        "Flappy Bird as much as we enjoyed building it!"
    );
    info.setPosition(30, 250);

    // Thiết lập backButton
    backButton.setSize({ 150, 50 });
    backButton.setPosition(centerX - backButton.getGlobalBounds().width / 2, 500); // Căn giữa button: centerX - width/2

    // Thiết lập backText
    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color::White);

    // Căn giữa backText trong backButton
    sf::FloatRect buttonBounds = backButton.getGlobalBounds();
    sf::FloatRect textBounds = backText.getGlobalBounds();
    float textX = buttonBounds.left + (buttonBounds.width - textBounds.width) / 2;
    float textY = buttonBounds.top + (buttonBounds.height - textBounds.height) / 2 - textBounds.top; // Điều chỉnh căn giữa dọc
    backText.setPosition(textX, textY);
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

    float layer4Speed = 200.0f; // Pixel/giây
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

    isBackHovered = backButton.getGlobalBounds().contains(mouse);
    backButton.setFillColor(isBackHovered ? sf::Color(7, 52, 153, 80) : sf::Color(7, 52, 153, 160));
}

void AboutScreen::draw() {
    window.draw(backgroundSprite1);
    window.draw(backgroundSprite2);
    window.draw(backgroundSprite3);

    window.draw(title);
    window.draw(info);
    window.draw(backButton);
    window.draw(backText);
}
