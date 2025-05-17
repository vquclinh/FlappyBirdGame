#include "SettingsScreen.h"

bool isMusicOn = true;

sf::Music backgroundMusic;

SettingsScreen::SettingsScreen(sf::RenderWindow& win) : window(win) {
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

    // Scale ảnh theo kích thước cửa sổ 
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
    backgroundSpriteLayer4_2.setPosition(windowSize.x, 0);
    backgroundSpriteLayer6_2.setPosition(windowSize.x, 0);

    // Text và button
    float windowWidth = windowSize.x;
    float centerX = windowWidth / 2;

    title.setFont(font);
    title.setString("Settings");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color(198, 23, 133, 225));
    title.setPosition(centerX - title.getGlobalBounds().width / 2, 50);

    // Thiết lập backButton
    backButton.setSize({ 100, 50 });
    backButton.setPosition(centerX - 75, 500); // Căn giữa button

    // Thiết lập backText
    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color::White);

    // Căn giữa backText trong backButton
    sf::FloatRect buttonBounds = backButton.getGlobalBounds();
    sf::FloatRect textBounds = backText.getGlobalBounds();
    float textX = buttonBounds.left + (buttonBounds.width - textBounds.width) / 2;
    float textY = buttonBounds.top + (buttonBounds.height - textBounds.height) / 2 - textBounds.top;
    backText.setPosition(textX, textY);

    // Nút âm thanh
    soundButton.setSize({ 250, 50 });
    soundButton.setPosition(centerX - 125, 400);

    soundText.setFont(font);
    soundText.setCharacterSize(24);
    soundText.setFillColor(sf::Color::White);
    soundText.setString("Sound: ON");

    // Căn giữa text trong button
    sf::FloatRect sbBounds = soundButton.getGlobalBounds();
    sf::FloatRect stBounds = soundText.getGlobalBounds();
    float stX = sbBounds.left + (sbBounds.width - stBounds.width) / 2;
    float stY = sbBounds.top + (sbBounds.height - stBounds.height) / 2 - 5.f;
    soundText.setPosition(stX, stY);
}

SettingsScreen::~SettingsScreen() {
    
}

void SettingsScreen::handleEvent(sf::Event& event, ScreenState& state) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));

        if (backButton.getGlobalBounds().contains(mouse)) {
            state = ScreenState::MAINMENU;
        }

        if (soundButton.getGlobalBounds().contains(mouse)) {
            isMusicOn = !isMusicOn;
            soundText.setString(isMusicOn ? "Sound: ON" : "Sound: OFF");

            // Cập nhật lại vị trí text để căn giữa
            sf::FloatRect sb = soundButton.getGlobalBounds();
            sf::FloatRect st = soundText.getGlobalBounds();
            float stX = sb.left + (sb.width - st.width) / 2;
            float stY = sb.top + (sb.height - st.height) / 2 - 5.f;
            soundText.setPosition(stX, stY);
            if (isMusicOn) {
                backgroundMusic.play();
            }
            else {
                backgroundMusic.pause();
            }
        }
    }
}

void SettingsScreen::update() {
    sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);

    // Di chuyển layer4 (hàng rào) với tốc độ nhanh hơn
    float layer4Speed = 100.0f; // Pixel/giây
    float deltaTime = 1.0f / 60.0f; // Ta đã set Target FPS bên ngoài khi tạo window là 60FPS 
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

    isBackHovered = backButton.getGlobalBounds().contains(mouse);
    backButton.setFillColor(isBackHovered ? sf::Color(7, 52, 153, 80) : sf::Color(7, 52, 153, 160));

    isSoundHovered = soundButton.getGlobalBounds().contains(mouse);
    soundButton.setFillColor(isSoundHovered ? sf::Color(7, 153, 52, 80) : sf::Color(7, 153, 52, 160));
}

void SettingsScreen::draw() {
    window.draw(backgroundSpriteLayer1);
    window.draw(backgroundSpriteLayer2);
    window.draw(backgroundSpriteLayer3);
    window.draw(backgroundSpriteLayer4_1);
    window.draw(backgroundSpriteLayer4_2);
    window.draw(backgroundSpriteLayer5);
    window.draw(backgroundSpriteLayer6_1);
    window.draw(backgroundSpriteLayer6_2);

    window.draw(title);
    window.draw(backButton);
    window.draw(backText);

    window.draw(soundButton);
    window.draw(soundText);
}

void AudioSystem::Init() {
    if (!backgroundMusic.openFromFile("Assets/Sounds/backgroundsound.mp3")) {
        std::cerr << "Failed to load background music!" << std::endl;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
}

void AudioSystem::Update() {
    if (isMusicOn && backgroundMusic.getStatus() != sf::Music::Playing) {
        backgroundMusic.play();
    }
}

void AudioSystem::Unload() {
    backgroundMusic.stop();
}