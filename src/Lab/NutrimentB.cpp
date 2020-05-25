#include "NutrimentB.hpp"
#include "Application.hpp"
#include "SimpleBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "PoisonBacterium.hpp"

unsigned int NutrimentB::nutriBCounter(0);

NutrimentB::NutrimentB(Quantity quantity, const Vec2d& position)
    : Nutriment(quantity, position)
{ ++ nutriBCounter; }

j::Value const& NutrimentB::getConfig() const
{
    return getAppConfig()["nutriments"]["B"];
}

Quantity NutrimentB::eatenBy(const Bacterium& bacterie)
{
    return bacterie.eatableQuantity(*this);
}

Quantity NutrimentB::eatenBy(const SimpleBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity() / getShortConfig().nutrimentB_resistance_factor);
}

Quantity NutrimentB::eatenBy(const SwarmBacterium& bacterie)
{
    return - getShortConfig().nutrimentB_poison_factor * takeQuantity(bacterie.getMaxEatableQuantity());
}

Quantity NutrimentB::eatenBy(const TwitchingBacterium& bacterie)
{
    return getShortConfig().nutrimentB_nutritive_factor * takeQuantity(bacterie.getMaxEatableQuantity());
}

Quantity NutrimentB::eatenBy(const PoisonBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity() / getShortConfig().nutrimentB_resistance_factor);
}

double NutrimentB::getScoreCoefficient(const Bacterium& bacterie) const
{
    return bacterie.getScoreCoefficient(*this);
}

double NutrimentB::getScoreCoefficient(const SimpleBacterium& bacterie) const
{
    return 1 / getShortConfig().nutrimentB_resistance_factor;
}

double NutrimentB::getScoreCoefficient(const SwarmBacterium& bacterie) const
{
    return - 1;
}

double NutrimentB::getScoreCoefficient(const TwitchingBacterium& bacterie) const
{
    return getShortConfig().nutrimentB_nutritive_factor;
}

double NutrimentB::getScoreCoefficient(const PoisonBacterium& bacterie) const
{
   return 1 / getShortConfig().nutrimentB_resistance_factor;
}

unsigned int NutrimentB::getNutriBCounter()
{
    return nutriBCounter;
}

NutrimentB::~NutrimentB()
{
    -- nutriBCounter;
}
