#include "PoisonBacterium.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Poison.hpp"
#include "Application.hpp"

unsigned int PoisonBacterium::poisonCounter(0);

PoisonBacterium::PoisonBacterium(const Vec2d& position)
    : SwimmingBacterium(position, Vec2d::fromRandomAngle(), uniform(getShortConfig().poisonbact_min_radius, getShortConfig().poisonbact_max_radius),
                        uniform(getShortConfig().poisonbact_min_energy, getShortConfig().poisonbact_max_energy), getConfig()["color"],
{ {"speed", MutableNumber::positive(getConfig()["speed"])},
    {"tumble better prob", MutableNumber::positive(getConfig()["tumble"]["better"])},
    {"tumble worse prob", MutableNumber::positive(getConfig()["tumble"]["worse"])}
}), delayPoison(sf::Time::Zero)
{
    ++poisonCounter;
}

PoisonBacterium::PoisonBacterium(const PoisonBacterium& other)
    : SwimmingBacterium(other)
{
    ++poisonCounter;
}

Quantity PoisonBacterium::eatableQuantity(NutrimentA& nutriment) const
{
    return nutriment.eatenBy(*this);
}

Quantity PoisonBacterium::eatableQuantity(NutrimentB& nutriment) const
{
    return nutriment.eatenBy(*this);
}

Quantity PoisonBacterium::eatableQuantity(Poison& nutriment) const
{
    return nutriment.eatenBy(*this);
}

double PoisonBacterium::getScoreCoefficient(const NutrimentA& nutriment) const
{
    return nutriment.getScoreCoefficient(*this);
}

double PoisonBacterium::getScoreCoefficient(const NutrimentB& nutriment) const
{
    return nutriment.getScoreCoefficient(*this);
}

double PoisonBacterium::getScoreCoefficient(const Poison& poison) const
{
    return poison.getScoreCoefficient(*this);
}

j::Value const& PoisonBacterium::getConfig() const
{
    return getAppConfig()["poison bacterium"];
}

PoisonBacterium* PoisonBacterium::clone() const
{
    return new PoisonBacterium(*this);
}

void PoisonBacterium::dropPoison() const
{
    getAppEnv().addNutriment(new Poison(getPosition()));
}

unsigned int PoisonBacterium::getPoisonCounter()
{
    return poisonCounter;
}

void PoisonBacterium::move(sf::Time dt)
{
    SwimmingBacterium::move(dt);

    if(delayPoison >= getShortConfig().poisonbact_poison_delay) {
        dropPoison();
        delayPoison = sf::Time::Zero;
    } else
        delayPoison += dt;
}

PoisonBacterium::~PoisonBacterium()
{
    --poisonCounter;
}
