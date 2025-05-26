#include "ScoreManager.h"

ScoreManager::ScoreManager() : score(0), highestScore(0) {
	font.loadFromFile("Assets/Fonts/LilitaOne-Regular.ttf");
	scoreText.setFont(font);
	scoreText.setCharacterSize(70);
	scoreText.setFillColor(sf::Color(254, 45, 89, 225));
	scoreText.setPosition(230.f, 50.f);
	scoreText.setString("0");
};

void ScoreManager::reset() {
	score = 0;
	scoreText.setString("0");
}

void ScoreManager::increaseScore(){
	score += 1;
	scoreText.setString(std::to_string(score));
}

void ScoreManager::update(float dt) {
	if (score > highestScore) highestScore = score;
}

void ScoreManager::render(sf::RenderWindow& window) {
	window.draw(scoreText);
}

int ScoreManager::getScore() const {
	return score;
}

int ScoreManager::getHighestScore() const {
	return highestScore;
}