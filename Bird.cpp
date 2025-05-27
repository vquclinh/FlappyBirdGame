#include "Bird.h"
#include <iostream>

Bird::Bird() : velocity(0.f), gravity(3000.f), flapStrength(-750.f), startPos(190.f, 450.f), animationTimer(0.f) {
    texture1.loadFromFile("Assets/Images/bird1.png");
    texture2.loadFromFile("Assets/Images/bird2.png");
    birdImage.loadFromFile("Assets/Images/bird1.png");
    sprite.setTexture(texture1);

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);

    sprite.setPosition(startPos);
    sprite.setScale(0.1f, 0.1f);
}

void Bird::reset() {
    velocity = 0.f;
    sprite.setPosition(startPos);
    sprite.setTexture(texture1);
    sprite.setRotation(0);
    isFlapping = false;
    animationTimer = 0.f;
}

void Bird::flap() {
    velocity = flapStrength;
    timeSinceLastFlap = 0.f;
    isFlapping = true;
}

void Bird::update(float dt) {
    if (isFlapping) {
        velocity += gravity * dt;

        velocity = std::min(velocity, 500.f);
        velocity = std::max(velocity, flapStrength);
        sprite.move(0, velocity * dt);

        timeSinceLastFlap += dt;
        float currentRotation = sprite.getRotation();
        if (timeSinceLastFlap > 0.5f) {
            float targetAngle = 90.f;
            float rotationSpeed = 300.f; // độ mỗi giây
            float newRotation = currentRotation + rotationSpeed * dt;
            if (newRotation > targetAngle) newRotation = targetAngle;

            sprite.setRotation(newRotation);
        }
        else {
            sprite.setRotation(0);
        }

        animationTimer += dt;
        if (animationTimer >= animationFrameTime) {
            if (sprite.getTexture() == &texture1) {
                sprite.setTexture(texture2);
            }
            else {
                sprite.setTexture(texture1);
            }
            animationTimer = 0.f;
        }
    }
}

void Bird::helper(float dt) {
    if (isFlapping) {
        velocity += gravity * dt;

        velocity = std::min(velocity, 500.f);
        velocity = std::max(velocity, flapStrength);
        sprite.move(0, velocity * dt * 1.5f);

        sprite.setRotation(90);
        sprite.setTexture(texture1);
    }
}

void Bird::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Bird::getBounds() const {
    return sprite.getGlobalBounds();
}

float Bird::getX() const {
    return sprite.getPosition().x;
}

float Bird::getY() const {
    return sprite.getPosition().y;
}

bool Bird::isOutOfBounds() const {
    float y = sprite.getPosition().y;
    return y > 710;
}

const sf::Sprite& Bird::getSprite() const {
    return sprite;
}

const sf::Image& Bird::getImage() const {
    return birdImage;
}