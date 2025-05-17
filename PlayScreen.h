#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"
//#include "Bird.h"
//#include "PipeManager.h"
//#include "ScoreManager.h"

class PlayGame {
public:
    PlayGame(sf::RenderWindow& window);
    void handleInput(const sf::Event& event, ScreenState& state);
    void update(float dt);
    void render();

private:
    enum GameState { Playing, GameOver };
    GameState gameState;

    sf::RenderWindow& window;

    // Background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Panel 
    sf::Texture panelTexture;
    sf::Sprite panelSprite;

    // UI
    sf::Font font;
    sf::Text playerLabelText, playerNameText, scoreLabel, highScoreLabel, scoreValue, highScoreValue, restartText;

    int highestScore = 0;
    int score = 0;

    // Game logic objects
    //Bird bird;
    //PipeManager pipeManager;
    //ScoreManager scoreManager;

    // Back Button
    sf::Texture backTexture;
    sf::Sprite backSprite;
    bool isBackHovered = false;

    void loadBackground();
    void setupUI();
    void restart();
};
