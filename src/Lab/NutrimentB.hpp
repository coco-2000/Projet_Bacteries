#pragma once
#include "Nutriment.hpp"

class NutrimentB: public Nutriment
{
public :
    NutrimentB(Quantity quantity, const Vec2d& position);
    j::Value const& getConfig() const;
};
