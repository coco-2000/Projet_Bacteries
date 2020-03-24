#include "NutrimentA.hpp"
#include "Application.hpp"

NutrimentA::NutrimentA(Quantity quantity, const Vec2d& position)
    : Nutriment(quantity, position)
{}

j::Value const& NutrimentA::getConfig() const
{
    return getAppConfig()["nutriments"]["A"];
}
