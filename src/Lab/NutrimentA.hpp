#pragma once
#include "Nutriment.hpp"

class NutrimentA: public Nutriment
{
public :
    NutrimentA(Quantity quantity, const Vec2d& position);
    j::Value const& getConfig() const;
};
