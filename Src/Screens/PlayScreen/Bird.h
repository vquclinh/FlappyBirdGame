#pragma once

#include <SFML/Graphics.hpp>

class Bird {
public:
	Bird();
	void reset();
	void flap();
	void update(float dt);
	void helper(float dt);
	void render(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	float getX() const;
	float getY() const;
	bool isOutOfBounds() const;
	const sf::Sprite& getSprite() const;
	const sf::Image& getImage() const;
private:
	sf::Sprite sprite;
	sf::Texture texture1;
	sf::Texture texture2;
	sf::Image birdImage;
	float velocity;
	float gravity;
	float flapStrength;

	sf::Vector2f startPos;

	float timeSinceLastFlap = 0.f;
	float animationTimer;
	bool isFlapping = false;
	static constexpr float animationFrameTime = 0.01f;
};