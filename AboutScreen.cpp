#include "AboutScreen.h"

AboutScreen::AboutScreen(sf::RenderWindow& win) : window(win) {
    font.loadFromFile("assets/fonts/LilitaOne-Regular.ttf");

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
        "This Flappy Bird game is a collaborative project developed by Vo Quoc Linh, a student of the Advanced Program in Computer Science (APCS),\n"
        "Cohort 24, at the University of Science – Vietnam National University, Ho Chi Minh City, in collaboration with Nguyen Thanh Nhat, an Infor-\n"
        "-mation Technology student, Cohort 24, at the same university.\n\n"

        "Inspired by the original Flappy Bird game created by Vietnamese developer Nguyen Ha Dong, this project aims to recreate the fun and challe-\n"
        "-nge of the classic game while adding our own features and improvements.\n\n"

        "Through this project, we have applied our knowledge of C++ and SFML to build a complete game application with a user-friendly interface,\n"
        "customizable settings, and smooth gameplay.\n\n"

        "We hope you enjoy playing our version of Flappy Bird as much as we enjoyed building it!\n"
    );
    info.setPosition(200, 180);

    // Thiết lập backButton
    backButton.setSize({ 150, 50 });
    backButton.setFillColor(sf::Color(7, 52, 153, 110));
    backButton.setPosition(centerX - 75, 500); // Căn giữa button: centerX - width/2

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

void AboutScreen::draw() {
    window.draw(backgroundSpriteLayer1);
    window.draw(backgroundSpriteLayer2);
    window.draw(backgroundSpriteLayer3);
    window.draw(backgroundSpriteLayer4_1);
    window.draw(backgroundSpriteLayer4_2);
    window.draw(backgroundSpriteLayer5);
    window.draw(backgroundSpriteLayer6_1);
    window.draw(backgroundSpriteLayer6_2);

    window.draw(title);
    window.draw(info);
    window.draw(backButton);
    window.draw(backText);
}
