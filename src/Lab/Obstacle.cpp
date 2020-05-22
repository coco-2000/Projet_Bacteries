#include "Obstacle.hpp"
#include "../Utility/Utility.hpp"
#include "Application.hpp"

Obstacle::Obstacle(const Vec2d &position)
    : CircularBody (position, getAppConfig()["obstacle"]["radius"].toDouble())
{}

void Obstacle::drawOn(sf::RenderTarget &target) const
{
    const auto border = buildAnnulus(getPosition(), getRadius(), sf::Color::Black, 5);
    target.draw(border);
}
