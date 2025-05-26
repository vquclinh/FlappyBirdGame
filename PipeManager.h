#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bird.h"

class PipeManager {
private:
	struct PipePair {
		sf::Sprite topPipe;
		sf::Sprite botPipe;
		bool passed = false;
	};

	std::vector<PipePair> pipes;
	sf::Texture pipeTexture;
	sf::Image pipeImage;

	float spawnTimer;
	float spawnInterval;
	float pipeSpeed;

	float gapSize;
	float minY;
	float maxY;

	void spawnPipe();
public:
	PipeManager();

	void reset();
	void update(float dt);
	void render(sf::RenderWindow& window);
	bool birdPassedPipe(float birdX);

	// Hàm dùng để check xem pixel va chạm có phải là pixel trống không
	bool pixelPerfectCollision(
		const sf::Sprite& pipeSprite,
		const sf::Sprite& birdSprite,
		const sf::Image& birdImage);
	// Hàm check va chạm
	bool checkCollision(const sf::Sprite& birdSprite, const sf::Image& birdImage);
};