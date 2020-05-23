#pragma once
#include "CircularBody.hpp"
#include "../Interface/Drawable.hpp"


class Obstacle : public CircularBody, public Drawable
{
public :
    Obstacle( Vec2d const& position);
    void drawOn(sf::RenderTarget& target) const override;
    j::Value const& getConfig() const;
};

