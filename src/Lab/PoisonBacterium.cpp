#include "PoisonBacterium.hpp"
#include "NutrimentA.hpp"
#include "NutrimentB.hpp"
#include "Poison.hpp"
#include "Application.hpp"

double PoisonBacterium::poisonCounter(0);

PoisonBacterium::PoisonBacterium(const Vec2d& position)
    : SimpleBacterium(position, Vec2d::fromRandomAngle(), uniform(getShortConfig().poisonbact_min_radius, getShortConfig().poisonbact_max_radius),
                      uniform(getShortConfig().poisonbact_min_energy, getShortConfig().poisonbact_max_energy),
                      getAppConfig()["poison bacterium"]["color"],
                      {{"speed", MutableNumber::positive(getConfig()["speed"])},
                       {"tumble better prob", MutableNumber::positive(getConfig()["tumble"]["better"])},
                       {"tumble worse prob", MutableNumber::positive(getConfig()["tumble"]["worse"])}})
{
    ++poisonCounter;
    resetDelay();
}

PoisonBacterium::PoisonBacterium(const PoisonBacterium& other)
    : SimpleBacterium(other)
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

PoisonBacterium::~PoisonBacterium()
{
    --poisonCounter;
}

void PoisonBacterium::dropPoison()
{
    getAppEnv().addNutriment(new Poison(getPosition()));
}

double PoisonBacterium::getPoisonCounter()
{
    return poisonCounter;
}

void PoisonBacterium::move(sf::Time dt)
{
    SimpleBacterium::move(dt);

    if(delayPoison >= getShortConfig().poisonbact_poison_delay)
    {
        dropPoison();
        resetDelay();
    }
    else
    {
        delayPoison += dt;
    }
}

void PoisonBacterium::resetDelay()
{
    delayPoison = sf::Time::Zero;
}
