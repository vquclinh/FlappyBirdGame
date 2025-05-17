#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

class RoundedRectangleShape : public sf::Shape {
public:
    explicit RoundedRectangleShape(const sf::Vector2f& size = { 0, 0 }, float radius = 0, std::size_t cornerPointCount = 8);

    void setSize(const sf::Vector2f& size);
    const sf::Vector2f& getSize() const;

    void setCornersRadius(float radius);
    float getCornersRadius() const;

    void setCornerPointCount(std::size_t count);
    std::size_t getCornerPointCount() const;

    virtual std::size_t getPointCount() const override;
    virtual sf::Vector2f getPoint(std::size_t index) const override;

private:
    sf::Vector2f m_size;
    float m_radius;
    std::size_t m_cornerPointCount;
};
