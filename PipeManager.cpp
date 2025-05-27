#include "PipeManager.h"
#include <cstdlib> // Để dùng seed random (srand)
#include <random>

PipeManager::PipeManager() : spawnTimer(0.f), spawnInterval(1.6f), pipeSpeed(43.f), gapSize(140.f), minY(300.f), maxY(550.f) {
	pipeTexture.loadFromFile("Assets/Images/pipe1.png");
	pipeImage.loadFromFile("Assets/Images/pipe1.png");
	std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void PipeManager::reset() {
	pipes.clear();
	spawnTimer = 0.f;
}

void PipeManager::spawnPipe() {
	float centerY = minY + std::rand() % static_cast<int>(maxY - minY);

	PipePair pair;
	pair.topPipe.setTexture(pipeTexture);
	pair.topPipe.setScale(3.7f, -2.5f);
	pair.topPipe.setPosition(480.f, centerY - gapSize / 2.f);

	pair.botPipe.setTexture(pipeTexture);
	pair.botPipe.setScale(3.7f, 2.5f);
	pair.botPipe.setPosition(480.f, centerY + gapSize / 2.f);

	pipes.push_back(pair);
}

void PipeManager::update(float dt) {
	spawnTimer += dt;

	if (spawnTimer >= spawnInterval) {
		spawnTimer = 0.f;
		spawnPipe();
	}
	
	for (auto& pair : pipes) {
		pair.topPipe.move(-pipeSpeed * dt * 5.f, 0);
		pair.botPipe.move(-pipeSpeed * dt * 5.f, 0);
	}

	pipes.erase(std::remove_if(pipes.begin(), pipes.end(), [](const PipePair& pair) {
		return pair.topPipe.getPosition().x + pair.botPipe.getGlobalBounds().width < 0;
		}), pipes.end());
}

bool PipeManager::checkCollision(const sf::Sprite& birdSprite, const sf::Image& birdImage) {
	sf::FloatRect birdBounds = birdSprite.getGlobalBounds();

	for (const auto& pair : pipes) {
		if (pixelPerfectCollision(pair.topPipe, birdSprite, birdImage)) return true;
		if (pixelPerfectCollision(pair.botPipe, birdSprite, birdImage)) return true;
	}
	return false;
}

bool PipeManager::birdPassedPipe(float birdX) {
	for (auto& pair : pipes) {
		if (!pair.passed && pair.topPipe.getPosition().x + pair.topPipe.getGlobalBounds().width / 2.f < birdX) {
			pair.passed = true;
			return true;
		}
	}
	return false;
}

void PipeManager::render(sf::RenderWindow& window) {
	for (const auto& pair : pipes) {
		window.draw(pair.topPipe);
		window.draw(pair.botPipe);
	}
}

bool PipeManager::pixelPerfectCollision(
	const sf::Sprite& pipeSprite,
	const sf::Sprite& birdSprite,
	const sf::Image& birdImage)
{
	sf::FloatRect intersection;
	if (!pipeSprite.getGlobalBounds().intersects(birdSprite.getGlobalBounds(), intersection))
		return false;

	const sf::Transform& pipeInverse = pipeSprite.getInverseTransform();
	const sf::Transform& birdInverse = birdSprite.getInverseTransform();

	sf::IntRect pipeTexRect = pipeSprite.getTextureRect();
	sf::IntRect birdTexRect = birdSprite.getTextureRect();

	for (int x = static_cast<int>(intersection.left); x < intersection.left + intersection.width; ++x) {
		for (int y = static_cast<int>(intersection.top); y < intersection.top + intersection.height; ++y) {
			sf::Vector2f pipeLocal = pipeInverse.transformPoint(static_cast<float>(x), static_cast<float>(y));
			sf::Vector2f birdLocal = birdInverse.transformPoint(static_cast<float>(x), static_cast<float>(y));

			int px = static_cast<int>(pipeLocal.x);
			int py = static_cast<int>(pipeLocal.y);
			int bx = static_cast<int>(birdLocal.x);
			int by = static_cast<int>(birdLocal.y);

			// Xử lý scale âm (ống trên bị lật)
			if (pipeSprite.getScale().y < 0)
				py = pipeTexRect.height - py - 1;

			if (pipeSprite.getScale().x < 0)
				px = pipeTexRect.width - px - 1;

			if (birdSprite.getScale().y < 0)
				by = birdTexRect.height - by - 1;

			if (birdSprite.getScale().x < 0)
				bx = birdTexRect.width - bx - 1;

			if (px >= 0 && px < pipeTexRect.width && py >= 0 && py < pipeTexRect.height &&
				bx >= 0 && bx < birdTexRect.width && by >= 0 && by < birdTexRect.height) {

				sf::Color pipePixel = pipeImage.getPixel(pipeTexRect.left + px, pipeTexRect.top + py);
				sf::Color birdPixel = birdImage.getPixel(birdTexRect.left + bx, birdTexRect.top + by);

				// Cả hai pixel đều không trong suốt
				if (pipePixel.a > 0 && birdPixel.a > 0)
					return true;
			}
		}
	}
	return false;
}

bool PipeManager::checkBirdDead(const sf::Sprite& birdSprite) {
	for (auto& pair : pipes) {
		float center = pair.topPipe.getPosition().x + pair.topPipe.getGlobalBounds().width / 2;
		if (birdSprite.getPosition().x + birdSprite.getGlobalBounds().width / 2 >= center && birdSprite.getPosition().y < 0) return false;
	}

	return true;
}
