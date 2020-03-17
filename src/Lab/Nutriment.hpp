#pragma once
#include "CircularBody.hpp"
#include "Utility/Types.hpp"
#include "Application.hpp"


class Nutriment : public CircularBody
{
public :
    Nutriment(Quantity quantity, const Vec2d& position);
    Quantity takeQuantity(Quantity prelevement);
    void setQuantity(Quantity quantity);
    void drawOn(sf::RenderTarget& target) const;
    j::Value const& getConfig() const;




private :
    Quantity quantity_;
};
