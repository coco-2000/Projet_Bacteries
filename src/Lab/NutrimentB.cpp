#include "NutrimentB.hpp"
#include "Application.hpp"

NutrimentB::NutrimentB(Quantity quantity, const Vec2d& position)
    : Nutriment(quantity, position)
{}

j::Value const& NutrimentB::getConfig() const
{
    return getAppConfig()["nutriments"]["B"];
}
