#include "RoundedRectangleShape.h"

RoundedRectangleShape::RoundedRectangleShape(const sf::Vector2f& size, float radius, std::size_t cornerPointCount)
    : m_size(size), m_radius(radius), m_cornerPointCount(cornerPointCount)
{
    if (m_radius > m_size.x / 2.f || m_radius > m_size.y / 2.f) {
        m_radius = std::min(m_size.x / 2.f, m_size.y / 2.f);
    }
    update();
}

void RoundedRectangleShape::setSize(const sf::Vector2f& size) {
    m_size = size;
    update();
}

const sf::Vector2f& RoundedRectangleShape::getSize() const {
    return m_size;
}

void RoundedRectangleShape::setCornersRadius(float radius) {
    m_radius = radius;
    update();
}

float RoundedRectangleShape::getCornersRadius() const {
    return m_radius;
}

void RoundedRectangleShape::setCornerPointCount(std::size_t count) {
    m_cornerPointCount = std::max(count, std::size_t(2));
    update();
}

std::size_t RoundedRectangleShape::getCornerPointCount() const {
    return m_cornerPointCount;
}

std::size_t RoundedRectangleShape::getPointCount() const {
    return m_cornerPointCount * 4;
}

sf::Vector2f RoundedRectangleShape::getPoint(std::size_t index) const {
    std::size_t corner = index / m_cornerPointCount;
    float angle = (index % m_cornerPointCount) * 90.f / (m_cornerPointCount - 1);
    float rad = angle * 3.14159265f / 180.f;

    sf::Vector2f center;
    switch (corner) {
    case 0: center.x = m_size.x - m_radius; center.y = m_radius; break;
    case 1: center.x = m_radius; center.y = m_radius; break;
    case 2: center.x = m_radius; center.y = m_size.y - m_radius; break;
    case 3: center.x = m_size.x - m_radius; center.y = m_size.y - m_radius; break;
    }

    return {
        center.x + std::cos(rad) * m_radius,
        center.y - std::sin(rad) * m_radius
    };
}
