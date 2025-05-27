#include "PlayScreen.h"
#include <iostream>
#include <sstream>

PlayGame::PlayGame(sf::RenderWindow& win)
    : window(win), gameState(Preparing)
{
    font.loadFromFile("Assets/Fonts/LilitaOne-Regular.ttf");
    loadBackground();
    restart();  
    overlay.setSize(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 120));
    box.setSize(sf::Vector2f(300.f, 150.f));
    box.setPosition((Screen_w - box.getSize().x) / 2, (Screen_h - box.getSize().y) / 2);
    box.setFillColor(sf::Color(255, 255, 255, 255));
    box.setOutlineThickness(2.f);
    box.setOutlineColor(sf::Color(0, 0, 0, 200));
}

void PlayGame::loadBackground() {
    // Tải background
    playBoundsTexture.loadFromFile("Assets/Images/background.png");
    playBoundsSprite1.setTexture(playBoundsTexture);
    playBoundsSprite2.setTexture(playBoundsTexture);
    playBoundsSprite3.setTexture(playBoundsTexture);

    sf::Vector2u textureSize = playBoundsTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;

    playBoundsSprite1.setScale(scaleX, scaleY);
    playBoundsSprite2.setScale(scaleX, scaleY);
    playBoundsSprite3.setScale(scaleX, scaleY);

    playBoundsSprite2.setPosition(windowSize.x, 0);
    playBoundsSprite3.setPosition(windowSize.x * 2, 0);

    // Back Button
    backButton.setSize({ 90, 30 });
    backButton.setPosition(20, Screen_h - 50);

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(22);
    backText.setFillColor(sf::Color::White);

    sf::FloatRect buttonBounds = backButton.getGlobalBounds();
    sf::FloatRect textBounds = backText.getGlobalBounds();
    backText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    backText.setPosition(backButton.getPosition().x + backButton.getSize().x / 2.f, backButton.getPosition().y + backButton.getSize().y / 2.f);
}

void PlayGame::setupUI() {
    // Player Name
    playerLabelText.setFont(font);
    playerLabelText.setString("Player: ");
    playerLabelText.setCharacterSize(22);
    playerLabelText.setFillColor(sf::Color(63, 59, 125));
    playerLabelText.setPosition(box.getPosition().x + 10.f, box.getPosition().y + 10.f);

    playerNameText.setFont(font);
    playerNameText.setString(playerName);
    playerNameText.setCharacterSize(22);
    playerNameText.setFillColor(sf::Color(137, 4, 133, 225));

    playerNameText.setPosition(playerLabelText.getPosition().x + playerLabelText.getGlobalBounds().width + 5.f, playerLabelText.getPosition().y);

    // Highest Score
    highScoreLabel.setFont(font);
    highScoreLabel.setString("Highest Score: ");
    highScoreLabel.setCharacterSize(22);
    highScoreLabel.setFillColor(sf::Color(63, 59, 125, 255));
    highScoreLabel.setPosition(box.getPosition().x + 10.f, box.getPosition().y + 40.f);

    highScoreValue.setFont(font);
    highScoreValue.setString(std::to_string(scoreManager.getHighestScore()));
    highScoreValue.setCharacterSize(22);
    highScoreValue.setFillColor(sf::Color(137, 4, 133, 225));
    
    highScoreValue.setPosition(highScoreLabel.getPosition().x + highScoreLabel.getGlobalBounds().width + 5.f, highScoreLabel.getPosition().y);

    // Score
    scoreLabel.setFont(font);
    scoreLabel.setString("Score: ");
    scoreLabel.setCharacterSize(22);
    scoreLabel.setFillColor(sf::Color(63, 59, 125, 255));
    scoreLabel.setPosition(box.getPosition().x + 10.f, box.getPosition().y + 70.f);

    scoreValue.setFont(font);
    scoreValue.setString(std::to_string(scoreManager.getScore()));
    scoreValue.setCharacterSize(22);
    scoreValue.setFillColor(sf::Color(137, 4, 133, 225)); // Màu khác ở đây

    scoreValue.setPosition(scoreLabel.getPosition().x + scoreLabel.getGlobalBounds().width + 5.f, scoreLabel.getPosition().y);
    
    // Restart
    restartText.setFont(font);
    restartText.setString("Press [SPACE] to Restart!");
    restartText.setCharacterSize(22);
    restartText.setFillColor(sf::Color::Red);
    restartText.setPosition(box.getPosition().x + 10.f, box.getPosition().y + 100.f);
}

void PlayGame::restart() {
    bird.reset();
    pipeManager.reset();
    scoreManager.reset();
    gameState = Preparing;
}

void PlayGame::handleInput(const sf::Event& event, ScreenState& state) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        if (gameState == Playing) bird.flap();
        else if (gameState == GameOver) restart();
        else if (gameState == Preparing) {
            gameState = Playing;
            bird.flap();
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse(sf::Mouse::getPosition(window));

        if (backButton.getGlobalBounds().contains(mouse)) {
            state = ScreenState::MAINMENU;
        }
    }
}

void PlayGame::update(float dt) {
    if (gameState == GameOver) return;
    setupUI();

    if (gameState == Playing) {
        pipeManager.update(dt);

        if (pipeManager.checkCollision(bird.getSprite(), bird.getImage()) || bird.isOutOfBounds() || !pipeManager.checkBirdDead(bird.getSprite())) {
            gameState = Falling;
        }

        if (pipeManager.birdPassedPipe(bird.getX() + bird.getBounds().width / 2.f)) {
            scoreManager.increaseScore();
        }
        scoreManager.update(dt);
    }

    if (gameState == Playing) bird.update(dt);
    else bird.helper(dt);
    if (gameState == Falling && bird.getY() > window.getSize().y - 10.f) {
        gameState = GameOver;
    }

    sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(window);

    float layer4Speed = 200.0f;
    float deltaTime = 1.0f / 60.0f;
    float layer4Width = playBoundsSprite1.getGlobalBounds().width;

    playBoundsSprite1.move(-layer4Speed * deltaTime, 0);
    playBoundsSprite2.move(-layer4Speed * deltaTime, 0);
    playBoundsSprite3.move(-layer4Speed * deltaTime, 0);

    // Đặt lại vị trí khi sprite ra khỏi màn hình
    if (playBoundsSprite1.getPosition().x <= -layer4Width) {
        playBoundsSprite1.setPosition(playBoundsSprite3.getPosition().x + layer4Width, 0);
    }
    if (playBoundsSprite2.getPosition().x <= -layer4Width) {
        playBoundsSprite2.setPosition(playBoundsSprite1.getPosition().x + layer4Width, 0);
    }
    if (playBoundsSprite3.getPosition().x <= -layer4Width) {
        playBoundsSprite3.setPosition(playBoundsSprite2.getPosition().x + layer4Width, 0);
    }

    isBackHovered = backButton.getGlobalBounds().contains(mouse);
    backButton.setFillColor(isBackHovered ? sf::Color(7, 52, 153, 80) : sf::Color(7, 52, 153, 160));
}

void PlayGame::render() {
    window.draw(playBoundsSprite1);
    window.draw(playBoundsSprite2);
    window.draw(playBoundsSprite3);

    pipeManager.render(window);
    bird.render(window);
    scoreManager.render(window);
    
    if (gameState == Falling || gameState == GameOver) window.draw(overlay);
    
    // Khi GameOver, vẽ panel gồm tên, score vừa đạt và score kỉ lục.
    if (gameState == GameOver) {
        window.draw(box);
        window.draw(playerLabelText);
        window.draw(playerNameText);
        window.draw(highScoreLabel);
        window.draw(highScoreValue);
        window.draw(scoreLabel);
        window.draw(scoreValue);
        window.draw(restartText);
    }

    window.draw(backButton);
    window.draw(backText);
}