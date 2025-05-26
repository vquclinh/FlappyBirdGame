#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"
#include "Bird.h"
#include "PipeManager.h"
#include "ScoreManager.h"

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    void handleInput(const sf::Event& event, ScreenState& state);
    void update(float dt);
    void render();

private:
    enum GameState { Playing, GameOver, Falling, Preparing };
    GameState gameState;

    sf::RenderWindow& window;

    // Background
    sf::Texture playBoundsTexture;
    sf::Sprite playBoundsSprite1;
    sf::Sprite playBoundsSprite2;
    sf::Sprite playBoundsSprite3;

    // UI
    sf::Font font;
    sf::Text playerLabelText, playerNameText, scoreLabel, highScoreLabel, scoreValue, highScoreValue, restartText;

    // Game logic objects
    Bird bird;
    PipeManager pipeManager;
    ScoreManager scoreManager;

    void loadBackground();
    void setupUI();
    void restart();

    sf::RectangleShape overlay;
    sf::RectangleShape box;

    // Nút Back
    bool isBackHovered = false;
    sf::RectangleShape backButton;
    sf::Text backText;
};
