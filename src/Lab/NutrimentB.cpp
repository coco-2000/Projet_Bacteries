#include "NutrimentB.hpp"
#include "Application.hpp"
#include "SimpleBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "PoisonBacterium.hpp"

NutrimentB::NutrimentB(Quantity quantity, const Vec2d& position)
    : Nutriment(quantity, position)
{}

j::Value const& NutrimentB::getConfig() const
{
    return getAppConfig()["nutriments"]["B"];
}

Quantity NutrimentB::eatenBy(Bacterium& bacterie)
{
    return bacterie.eatableQuantity(*this);
}

Quantity NutrimentB::eatenBy(SimpleBacterium& bacterie)
{
    Quantity prelevement(bacterie.getMaxEatableQuantity() / getConfig()["resistance factor"].toDouble());
    return takeQuantity(prelevement);
}

Quantity NutrimentB::eatenBy(SwarmBacterium& bacterie)
{
    Quantity prelevement(bacterie.getMaxEatableQuantity());
    return -getConfig()["poison factor"].toDouble() * takeQuantity(prelevement);
}

Quantity NutrimentB::eatenBy(TwitchingBacterium& bacterie)
{
    Quantity prelevement(bacterie.getMaxEatableQuantity());
    return getConfig()["nutritive factor"].toDouble() * takeQuantity(prelevement);
}

Quantity NutrimentB::eatenBy(PoisonBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity() / getShortConfig().nutrimentB_resistance_factor);
}

double NutrimentB::getPositionScore(const Bacterium& bacterie) const
{
    return bacterie.getPositionScore(*this);
}

double NutrimentB::getPositionScore(const SimpleBacterium& bacterie) const
{
    return 1 / getShortConfig().nutrimentB_resistance_factor;
}

double NutrimentB::getPositionScore(const SwarmBacterium& bacterie) const
{
    return - 1;
}

double NutrimentB::getPositionScore(const TwitchingBacterium& bacterie) const
{
    return getShortConfig().nutrimentB_nutritive_factor;
}

double NutrimentB::getPositionScore(const PoisonBacterium& bacterie) const
{
    return 1 / getShortConfig().nutrimentB_resistance_factor;
}
