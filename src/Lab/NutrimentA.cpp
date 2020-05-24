#include "NutrimentA.hpp"
#include "Application.hpp"
#include "SimpleBacterium.hpp"
#include "SwarmBacterium.hpp"
#include "TwitchingBacterium.hpp"
#include "PoisonBacterium.hpp"

unsigned int NutrimentA::nutriACounter(0);

NutrimentA::NutrimentA(Quantity quantity, const Vec2d& position)
    : Nutriment(quantity, position)
{++ nutriACounter;}

j::Value const& NutrimentA::getConfig() const
{
    return getAppConfig()["nutriments"]["A"];
}

Quantity NutrimentA::eatenBy(const Bacterium& bacterie)
{
    return bacterie.eatableQuantity(*this);
}

Quantity NutrimentA::eatenBy(const SimpleBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity());
}

Quantity NutrimentA::eatenBy(const SwarmBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity());
}

Quantity NutrimentA::eatenBy(const TwitchingBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity());
}

Quantity NutrimentA::eatenBy(const PoisonBacterium& bacterie)
{
    return takeQuantity(bacterie.getMaxEatableQuantity());
}

double NutrimentA::getScoreCoefficient(const Bacterium& bacterie) const
{
    return bacterie.getScoreCoefficient(*this);
}

double NutrimentA::getScoreCoefficient(const SimpleBacterium& bacterie) const
{
    return 1;
}

double NutrimentA::getScoreCoefficient(const SwarmBacterium& bacterie) const
{
    return 1;
}

double NutrimentA::getScoreCoefficient(const TwitchingBacterium& bacterie) const
{
    return 1;
}

double NutrimentA::getScoreCoefficient(const PoisonBacterium& bacterie) const
{
    return 1;
}

unsigned int NutrimentA::getNutriACounter()
{
    return nutriACounter;
}

NutrimentA::~NutrimentA()
{
    --nutriACounter;
}
