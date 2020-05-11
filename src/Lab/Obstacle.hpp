#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"

class Obstacle : public CircularBody, public Drawable
{
    Obstacle( Vec2d const& position, double radius);
    void drawOn(sf::RenderTarget& target) const override;
};
