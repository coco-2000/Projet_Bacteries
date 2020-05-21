#include "NutrimentA.hpp"
#include "Application.hpp"
#include "SimpleBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "PoisonBacterium.hpp"

NutrimentA::NutrimentA(Quantity quantity, const Vec2d& position)
    : Nutriment(quantity, position)
{}

j::Value const& NutrimentA::getConfig() const
{
    return getAppConfig()["nutriments"]["A"];
}

Quantity NutrimentA::eatenBy(Bacterium& bacterie)
{
    return bacterie.eatableQuantity(*this);
}

Quantity NutrimentA::eatenBy(SimpleBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity());
}

Quantity NutrimentA::eatenBy(SwarmBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity());
}

Quantity NutrimentA::eatenBy(TwitchingBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity());
}

Quantity NutrimentA::eatenBy(PoisonBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity());
}

double NutrimentA::getPositionScore(const Bacterium& bacterie) const
{
    return bacterie.getPositionScore(*this);
}

double NutrimentA::getPositionScore(const SimpleBacterium& bacterie) const
{
    return 1;
}

double NutrimentA::getPositionScore(const SwarmBacterium& bacterie) const
{
    return 1;
}

double NutrimentA::getPositionScore(const TwitchingBacterium& bacterie) const
{
    return 1;
}

double NutrimentA::getPositionScore(const PoisonBacterium& bacterie) const
{
    return 1;
}
