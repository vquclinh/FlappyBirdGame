#include "PlayScreen.h"
#include <iostream>
#include <sstream>

PlayGame::PlayGame(sf::RenderWindow& win)
    : window(win), gameState(Playing)
{
    loadBackground();
    restart();
}

void PlayGame::loadBackground() {
    // Tải background
    if (!backgroundTexture.loadFromFile("Assets/Images/full-bg.png")) {
        std::cerr << "Failed to load background image\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    float scaleX = window.getSize().x / static_cast<float>(backgroundTexture.getSize().x);
    float scaleY = window.getSize().y / static_cast<float>(backgroundTexture.getSize().y);
    float scale = std::max(scaleX, scaleY);

    backgroundSprite.setScale(scale, scale);
    backgroundSprite.setPosition(0.f, 0.f);

    sf::Vector2f spriteSize(backgroundTexture.getSize().x * scale, backgroundTexture.getSize().y * scale);
    if (spriteSize.x > window.getSize().x) {
        backgroundSprite.setPosition(-(spriteSize.x - window.getSize().x) / 2.f, backgroundSprite.getPosition().y);
    }
    if (spriteSize.y > window.getSize().y) {
        backgroundSprite.setPosition(backgroundSprite.getPosition().x, -(spriteSize.y - window.getSize().y) / 2.f);
    }

    // Tải và scale Panel.png
    if (!panelTexture.loadFromFile("Assets/Images/Panel.png")) {
        std::cerr << "Failed to load panel image\n";
    }
    panelSprite.setTexture(panelTexture);
    panelSprite.setPosition(5.f, -50.f);

    sf::Vector2u panelSize = panelTexture.getSize();
    float targetWidth = 350.f;
    float targetHeight = 410.f;
    float panelScaleX = targetWidth / static_cast<float>(panelSize.x);
    float panelScaleY = targetHeight / static_cast<float>(panelSize.y);
    panelSprite.setScale(panelScaleX, panelScaleY);

    // Tải và scale Back.png 
    if (!backTexture.loadFromFile("Assets/Images/Back.png")) {
        std::cerr << "Failed to load back image\n";
    }
    backSprite.setTexture(backTexture);
    backSprite.setPosition(130.f, 240.f);

    sf::Vector2u backSize = backTexture.getSize();
    float targetWidth2 = 100.f;
    float targetHeight2 = 100.f;
    float backScaleX = targetWidth2 / static_cast<float>(backSize.x);
    float backScaleY = targetHeight2 / static_cast<float>(backSize.y);
    backSprite.setScale(backScaleX, backScaleY);
}

void PlayGame::setupUI() {
    if (!font.loadFromFile("Assets/Fonts/LilitaOne-Regular.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    // Player Name
    playerLabelText.setFont(font);
    playerLabelText.setString("Player: ");
    playerLabelText.setCharacterSize(24);
    playerLabelText.setFillColor(sf::Color(63, 59, 125));
    playerLabelText.setPosition(50.f, 75.f);

    playerNameText.setFont(font);
    playerNameText.setString(playerName);
    playerNameText.setCharacterSize(24);
    playerNameText.setFillColor(sf::Color(137, 4, 133, 225));

    sf::FloatRect labelBounds = playerLabelText.getGlobalBounds();
    playerNameText.setPosition(labelBounds.left + labelBounds.width + 5.f, 75.f);

    // Highest Score
    highScoreLabel.setFont(font);
    highScoreLabel.setString("High Score: ");
    highScoreLabel.setCharacterSize(24);
    highScoreLabel.setFillColor(sf::Color(63, 59, 125, 255));
    highScoreLabel.setPosition(50.f, 110.f);

    highScoreValue.setFont(font);
    highScoreValue.setString(std::to_string(highestScore));
    highScoreValue.setCharacterSize(24);
    highScoreValue.setFillColor(sf::Color(137, 4, 133, 225));
    
    highScoreValue.setPosition(highScoreLabel.getPosition().x + highScoreLabel.getLocalBounds().width, 110.f);

    // Score
    scoreLabel.setFont(font);
    scoreLabel.setString("Score: ");
    scoreLabel.setCharacterSize(24);
    scoreLabel.setFillColor(sf::Color(63, 59, 125, 255));
    scoreLabel.setPosition(50.f, 145.f);

    scoreValue.setFont(font);
    scoreValue.setString(std::to_string(score));
    scoreValue.setCharacterSize(24);
    scoreValue.setFillColor(sf::Color(137, 4, 133, 225)); // Màu khác ở đây

    scoreValue.setPosition(scoreLabel.getPosition().x + scoreLabel.getLocalBounds().width, 145.f);
    
    // Restart
    restartText.setFont(font);
    restartText.setString("Press R to Restart!");
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::Red);
    restartText.setPosition(50.f, 180.f);
}

void PlayGame::restart() {
    //bird.reset();
    //pipeManager.reset();
    //scoreManager.reset();
    gameState = Playing;
}

void PlayGame::handleInput(const sf::Event& event, ScreenState& state) {
    //if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
    //    if (gameState == Playing) bird.flap();
    //    else if (gameState == GameOver) restart();
    //}

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));

        if (backSprite.getGlobalBounds().contains(mouse)) {
            state = ScreenState::MAINMENU;
        }
    }
}

void PlayGame::update(float dt) {
    if (gameState != Playing) return;

    //bird.update(dt);
    //pipeManager.update(dt);

    // Check collision
    //if (pipeManager.checkCollision(bird.getBounds()) || bird.isOutOfBounds()) {
    //    gameState = GameOver;
    //}

    // Update score
    //if (pipeManager.birdPassedPipe(bird.getX())) {
    //    scoreManager.increment();
    //}

    //scoreText.setString("Score: " + std::to_string(scoreManager.getScore()));
    
    setupUI();
}

void PlayGame::render() {
    window.setView(window.getDefaultView());
    window.draw(backgroundSprite);

    // Vẽ game area
    sf::RectangleShape rect(sf::Vector2f(game_w, game_h));
    float posX = (window.getSize().x - rect.getSize().x) / 2.f;
    float posY = (window.getSize().y - rect.getSize().y) / 2.f;
    rect.setPosition(posX, posY);
    rect.setFillColor(sf::Color(50, 150, 250));
    window.draw(rect);

    // Vẽ panel làm nền, sau đó vẽ các văn bản
    window.draw(panelSprite);
    window.draw(playerLabelText);
    window.draw(playerNameText);
    window.draw(highScoreLabel);
    window.draw(highScoreValue);
    window.draw(scoreLabel);
    window.draw(scoreValue);
    window.draw(restartText);

    window.draw(backSprite);
}