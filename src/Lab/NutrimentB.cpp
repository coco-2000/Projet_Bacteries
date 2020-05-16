#include "NutrimentB.hpp"
#include "Application.hpp"
#include "SimpleBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "TwitchingBacterium.hpp"

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
    return takeQuantity(bacterie.getMaxEatableQuantity() / getConfig()["resistance factor"].toDouble());
}

Quantity NutrimentB::eatenBy(SwarmBacterium& bacterie)
{
    Quantity prelevement(bacterie.getMaxEatableQuantity());
    return -getConfig()["poison factor"].toDouble() * testPrelevement(prelevement);
}

Quantity NutrimentB::eatenBy(TwitchingBacterium& bacterie)
{
    Quantity prelevement(bacterie.getMaxEatableQuantity());
    return takeQuantity(getConfig()["nutritive factor"].toDouble() * testPrelevement(prelevement));
}
