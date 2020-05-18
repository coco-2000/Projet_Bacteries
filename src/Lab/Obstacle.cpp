#include "Obstacle.hpp"
#include "../Utility/Utility.hpp"

Obstacle::Obstacle(const Vec2d &position, double radius)
    : CircularBody (position, radius)
{}

void Obstacle::drawOn(sf::RenderTarget &target) const
{
    const auto border = buildAnnulus(getPosition(), getRadius(), sf::Color::Black, 5);
    target.draw(border);
}
