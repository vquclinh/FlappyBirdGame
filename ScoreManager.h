#pragma once

#include <SFML/Graphics.hpp>

class ScoreManager {
private:
	sf::Font font;
	sf::Text scoreText;
	int score;
	int highestScore;
public:
	ScoreManager();

	void reset();
	void increaseScore();
	void update(float dt);
	void render(sf::RenderWindow& window);
	int getScore() const;
	int getHighestScore() const;
};